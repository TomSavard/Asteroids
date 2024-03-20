#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>  

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <list>
#include <math.h>
#include <time.h>

#include "interface/Menu.hpp"
#include "interface/GameOver.hpp"
#include "interface/GameOverMulti.hpp"
#include "interface/TableauDesScores.hpp"
#include "global_variables.hpp"
#include "Animation.hpp"
#include "objet/Entite.hpp"
#include "objet/asteroide.hpp"
#include "objet/tir.hpp"
#include "objet/player.hpp"

std::vector<std::string> parseEntiteData(const std::string& data) {
    std::istringstream iss(data);
    std::vector<std::string> values;
    std::string token;

    while (iss >> token) {
        values.push_back(token);
    }

    // if (values.size() != 7) {
    //     std::cout << values.size();
    //     throw std::runtime_error("Invalid data format: expected 7 tokens");
    // }

    return values;
}

void receiveDataFromServer(sf::TcpSocket& socket, std::list<Entite*> ListeDesEntites ,std::mutex& mutex) {
    while (true) {
        sf::Packet packet;
        if (socket.receive(packet) != sf::Socket::Done) {
            std::cerr << "Erreur lors de la réception des données" << std::endl;
            break;
        }

        std::string MessageReceived;
        packet >> MessageReceived;

        std::vector<std::string> NouvelEtat = parseEntiteData(MessageReceived);
        if (NouvelEtat.size() == 7){
            for (auto i : ListeDesEntites){
                if (i->getName() == NouvelEtat[0]){
                    if (i->getName() == "tir"){
                        tir *t1 = new tir();
                        t1->setTeam(1);
                        ListeDesEntites.push_back(t1);
                    }
                    try {
                        i->setx(std::stof(NouvelEtat[1]));
                        i->sety(std::stof(NouvelEtat[2]));
                        i->setvx(std::stof(NouvelEtat[3]));
                        i->setvy(std::stof(NouvelEtat[4]));
                        i->setangle(std::stof(NouvelEtat[5]));
                        i->setLife(std::stof(NouvelEtat[6]));
                    } catch (const std::exception& e) {
                        std::cerr << "Erreur de conversion : " << e.what() << std::endl;
                    }
                }
            }
        }

    }
        // std::lock_guard<std::mutex> lock(mutex);
}


int main() {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
    if (status != sf::Socket::Done) {
        std::cout << "Connection failed" << std::endl;
        return 1;
    }

    sf::Music musicHub;
    if (!musicHub.openFromFile("Ressources/audio/Dofus2.wav")) {
        throw std::runtime_error("Failed to load musicHub file");
    }
    musicHub.play();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroid Game");
    TableauDesScores LeScore;
    Menu menu(window, musicHub);
    std::tuple<std::string, float> action = menu.run();
    float VolumeSelected = std::get<1>(action);
    musicHub.stop();

    sf::SoundBuffer shootSoundBuffer;
    sf::Sound shootSound;
    if (!shootSoundBuffer.loadFromFile("Ressources/audio/tir.wav")) {
        throw std::runtime_error("Failed to load shootSound");
    }
    shootSound.setBuffer(shootSoundBuffer);
    int shootVolume = 8 * VolumeSelected;
    shootSound.setVolume(shootVolume);

    sf::SoundBuffer DeathSoundBuffer;
    sf::Sound DeathSound;
    if (!DeathSoundBuffer.loadFromFile("Ressources/audio/death.wav")) {
        throw std::runtime_error("Failed to load DeathSound");
    }
    DeathSound.setBuffer(DeathSoundBuffer);
    int DeathVolume = 100 * VolumeSelected;
    DeathSound.setVolume(DeathVolume);

    sf::SoundBuffer clickSoundBuffer;
    if (!clickSoundBuffer.loadFromFile("Ressources/audio/Bouton2.wav")) {
        throw std::runtime_error("Failed to load ClickSound");
    }
    sf::Sound clickSound;
    clickSound.setBuffer(clickSoundBuffer);

    sf::Clock clock;
    sf::Time timePerPacket = sf::seconds(0.02f);
    sf::Time elapsedTime = sf::Time::Zero;

    bool KeyPressed = false;
    std::vector<u_int8_t> StateVector(4, 0);

    sf::RenderWindow app(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Client");
    app.setFramerateLimit(60);

    sf::Texture t1, t2, t3, t4, t5, t6;
    try {
        if (!t1.loadFromFile("Ressources/animation/spaceship.png")) {
            throw std::runtime_error("Failed to load spaceship.png");
        }
        if (!t2.loadFromFile("Ressources/image/Space_Background.png")) {
            throw std::runtime_error("Failed to load Space_Background.png");
        }
        if (!t3.loadFromFile("Ressources/animation/spaceshipBlue.png")) {
            throw std::runtime_error("Failed to load spaceshipBlue.png");
        }
        if (!t4.loadFromFile("Ressources/animation/explosions/type_B.png")) {
            throw std::runtime_error("Failed to load type_B.png");
        }
        if (!t5.loadFromFile("Ressources/animation/fire_red.png")) {
            throw std::runtime_error("Failed to load fire_red.png");
        }
        if (!t6.loadFromFile("Ressources/animation/fire_blue.png")) {
            throw std::runtime_error("Failed to load fire_blue.png");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
    t1.setSmooth(true);
    t2.setSmooth(true);
    sf::Sprite background(t2);
    Animation sBulletRed(t5, 0, 0, 32, 64, 16, 0.8);
    Animation sBulletBlue(t6, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer1(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer2(t3, 40, 0, 40, 40, 1, 0);
    Animation sPlayer1_go(t1, 40, 40, 40, 40, 1, 0);
    Animation sPlayer2_go(t3, 40, 40, 40, 40, 1, 0);
    Animation sExplosion_ship(t4, 0, 0, 192, 192, 64, 0.5);

    std::list<Entite*> entities;
    std::mutex mutex;

    player* p1 = new player();
    p1->setTeam(1);
    p1->settings(sPlayer1, LargeurFenetre - 200, HauteurFenetre - 200, 180, 20);
    entities.push_back(p1);

    std::thread receiveThread(receiveDataFromServer, std::ref(socket), entities, std::ref(mutex));

    sf::Event event;
        while (app.isOpen())
    {
        elapsedTime += clock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            KeyPressed = true;
            StateVector[0] = 1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            KeyPressed = true;
            StateVector[1] = 1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            KeyPressed = true;
            StateVector[2] = 1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            KeyPressed = true;
            StateVector[3] = 1;
        }

        if (KeyPressed && elapsedTime >= timePerPacket) {
        std::cout << "\x1b[2K";

        sf::Packet sendPacket;
        std::string message = "";
        for (u_int8_t value : StateVector) {
            message += std::to_string(value);
        }
        sendPacket << message;

        if (socket.send(sendPacket) != sf::Socket::Done) {
            std::cout << "Failed to send data" << std::endl;
            return 1;
        }

        // std::cout << "Data sent successfully" << std::endl;
        elapsedTime = sf::Time::Zero;
        KeyPressed = false;
        StateVector.assign(4, 0);
        }

        // ÇA NE MARCHE PAS SANS CE TRUC, JSP POURQUOI
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                app.close();}
        }

        app.clear();
        app.draw(background);
        for (auto i : entities){
            if (i->getName() == "tir"){i->setAnim(sBulletRed);}
            i->draw(app);
        }
        app.display();
        



    }//fin while app.isOpen()


    socket.disconnect();

    return 0;
}
