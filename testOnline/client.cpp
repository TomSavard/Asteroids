#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp> // Pour SFML Graphics
#include <iostream>

int main() {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
    if (status != sf::Socket::Done) {
        std::cout << "Connection failed" << std::endl;
        return 1;
    }

    sf::Clock clock;
    sf::Time timePerPacket = sf::seconds(0.02f); // 20 millisecondes entre chaque envoi de paquet
    sf::Time elapsedTime = sf::Time::Zero; // Initialisation du temps écoulé

    bool running = true;
    bool KeyPressed = false;
    std::vector<u_int8_t> StateVector(4, 0); // [0]:space, [1]:right, [2]:left, [3]:up;

    while (running) {
        elapsedTime += clock.restart(); // Ajouter le temps écoulé depuis la dernière itération

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { KeyPressed = true; StateVector[0] = 1; } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { KeyPressed = true; StateVector[1] = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { KeyPressed = true; StateVector[2] = 1; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { KeyPressed = true; StateVector[3] = 1; }

        if (KeyPressed && elapsedTime >= timePerPacket) {
            std::cout << "\x1b[2K"; // Effacer la ligne actuelle du terminal

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

            std::cout << "Data sent successfully" << std::endl;
            elapsedTime = sf::Time::Zero; // Réinitialiser le temps écoulé après l'envoi de données
            KeyPressed = false;
            StateVector.assign(4, 0);
        }
    }

    // Fermer proprement la connexion
    socket.disconnect();

    return 0;
}
