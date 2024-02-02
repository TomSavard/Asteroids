/// Tom SAVARD 26/01/24 ///

// ! Not to do
// ? interrogation

///// TODO : Faire un code plus propre avec une classe entite et des sous-classes.
///// TODO : mise en place d'un écran game over.
///// TODO : Faire un code séparé avec des fichiers joints.
// TODO : Mise en place d'un mode multi en local

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include<math.h>
#include<time.h>

#include "interface/Menu.hpp"
#include "interface/GameOver.hpp"
#include "interface/TableauDesScores.hpp"
#include "global_variables.hpp"
#include "Animation.hpp"
#include "objet/Entite.hpp"
#include "objet/asteroide.hpp"
#include "objet/tir.hpp"
#include "objet/player.hpp"


bool isCollide(Entite *a,Entite *b)
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}



int main() {

sf::Music musicHub;
if (!musicHub.openFromFile("Ressources/audio/Dofus2.wav")) {std::cerr << "Failed to load music file" << std::endl; return -1;}
musicHub.play();
sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroid Game");
TableauDesScores LeScore;
Menu menu(window, musicHub);
Menu::ActionMenu action = menu.run();

musicHub.stop();

sf::SoundBuffer shootSoundBuffer;
sf::Sound shootSound;
if (!shootSoundBuffer.loadFromFile("Ressources/audio/tir.wav")) {
std::cerr << "Failed to load shoot sound file" << std::endl;}
shootSound.setBuffer(shootSoundBuffer);
int shootVolume = 3;
shootSound.setVolume(shootVolume);


sf::SoundBuffer DeathSoundBuffer;
sf::Sound DeathSound;
if (!DeathSoundBuffer.loadFromFile("Ressources/audio/death.wav")) {
std::cerr << "Failed to load death sound file" << std::endl;}
DeathSound.setBuffer(DeathSoundBuffer);
int DeathVolume = 100;
DeathSound.setVolume(DeathVolume);

sf::SoundBuffer clickSoundBuffer;
if (!clickSoundBuffer.loadFromFile("Ressources/audio/Bouton2.wav")) {std::cerr << "Failed to load click sound file" << std::endl;}
sf::Sound clickSound;
clickSound.setBuffer(clickSoundBuffer);


while(action == Menu::ActionMenu::Jouer){
    sf::Music musicGame;
    if (!musicGame.openFromFile("Ressources/audio/Glory.wav")) {std::cerr << "Failed to load music file" << std::endl; return -1;}
    int musicVolume = 30;
    musicGame.setVolume(musicVolume);
    musicGame.play();

    srand(time(0));

    sf::RenderWindow app(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroides!");
    app.setFramerateLimit(60);

    sf::Texture t1,t3,t4,t5,t6,t7;
    t1.loadFromFile("Ressources/animation/spaceship.png");
    // t2.loadFromFile("Ressources/image/Fond.png"); // * L'image rallenti le lancement
    t3.loadFromFile("Ressources/animation/explosions/type_C.png");
    t4.loadFromFile("Ressources/animation/rock.png");
    t5.loadFromFile("Ressources/animation/fire_red.png");
    t6.loadFromFile("Ressources/animation/rock_small.png");
    t7.loadFromFile("Ressources/animation/explosions/type_B.png");

    t1.setSmooth(true);
    // t2.setSmooth(true);

    // sf::Sprite background(t2);

    Animation sExplosion(t3, 0,0,256,256, 48, 0.5);
    Animation sRock(t4, 0,0,64,64, 16, 0.2);
    Animation sRock_small(t6, 0,0,64,64, 16, 0.2);
    Animation sBullet(t5, 0,0,32,64, 16, 0.8);
    Animation sPlayer(t1, 40,0,40,40, 1, 0);
    Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animation sExplosion_ship(t7, 0,0,192,192, 64, 0.5);


    std::list<Entite*> entities;

    for(int i=0;i<15;i++)
    {
        asteroide *a = new asteroide();
        a->settings(sRock, rand()%LargeurFenetre, rand()%HauteurFenetre, rand()%360, 25);
        entities.push_back(a);
    }

    player *p = new player();
    p->settings(sPlayer,200,200,0,20);
    entities.push_back(p);



    ///main loop///
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Space)
                {
                    tir *b = new tir();
                    b->settings(sBullet,p->x,p->y,p->angle,10);
                    entities.push_back(b);
                    shootSound.play();
                }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p->angle+=3;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) p->angle-=3;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) p->thrust=true;
        else p->thrust=false;


        for(auto a:entities)
            for(auto b:entities)
            {
                if (a->name=="asteroide" && b->name=="tir")
                    if ( isCollide(a,b) )
                        {
                            a->life=false;
                            b->life=false;

                            Entite *e = new Entite();
                            e->settings(sExplosion,a->x,a->y);
                            e->name="explosion";
                            entities.push_back(e);

                            LeScore.increaseScore(1);

                            for(int i=0;i<2;i++)
                            {
                            if (a->R==15) continue;
                            Entite *e = new asteroide();
                            e->settings(sRock_small,a->x,a->y,rand()%360,15);
                            entities.push_back(e);
                            }

                        }

                    if (a->name=="player" && b->name=="asteroide")
                        if ( isCollide(a,b) )
                        {
                            b->life=false;

                            Entite *e = new Entite();
                            e->settings(sExplosion_ship,a->x,a->y);
                            e->name="explosion";
                            entities.push_back(e);

                            app.close();
                            DeathSound.play();
                            musicGame.stop();

                            p->settings(sPlayer,LargeurFenetre/2,HauteurFenetre/2,0,20);
                            p->vx=0; p->vy=0;
                        }
                }  


            if (p->thrust)  p->anim = sPlayer_go;
            else   p->anim = sPlayer;


            for(auto e:entities)
                if (e->name=="explosion")
                if (e->anim.isEnd()) e->life=0;

                if (rand()%150==0)
                {
                    asteroide *a = new asteroide();
                    a->settings(sRock, 0,rand()%HauteurFenetre, rand()%360, 25);
                    entities.push_back(a);
                }

            for(auto i=entities.begin();i!=entities.end();)
            {
                Entite *e = *i;

                e->update();
                e->anim.update();

                if (e->life==false) {i=entities.erase(i); delete e;}
                else i++;
            }

    ///draw///
    app.clear();
    // app.draw(background);
    for(auto i:entities) i->draw(app);
    LeScore.drawScore(app);
    app.display();
    }

    sf::RenderWindow window(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroid Game Over");
    int scoreFinal = LeScore.getScore();
    GameOverScreen gameOverScreen(scoreFinal);
    bool actionRecu = false; //permet de savoir si le joueur a interragit
    while (window.isOpen() && !actionRecu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    clickSound.play(); // Jouer le son de clic
                    action = Menu::ActionMenu::Jouer;
                    actionRecu = true;
                    LeScore.reset();
                    std::cout << "Restarting the game..." << std::endl;}
                else if (event.key.code == sf::Keyboard::Q) {
                    clickSound.play(); // Jouer le son de clic
                    action = Menu::ActionMenu::Quitter;
                    actionRecu = true;
                    std::cout << "Exiting the game..." << std::endl;
                    window.close();}
            }
        }

        window.clear();
        gameOverScreen.draw(window);
        window.display();
    }
}// fin de la boucle while Action==Jouer
return 0;
}
