
///// TODO : Faire un code plus propre avec une classe entite et des sous-classes.
///// TODO : mise en place d'un écran game over.
///// TODO : Faire un code séparé avec des fichiers joints.
///// TODO : Mise en place d'un mode multi en local
///// TODO : Mettre en place une immunité au début 

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
#include "interface/GameOverMulti.hpp"
#include "interface/TableauDesScores.hpp"
#include "global_variables.hpp"
#include "Animation.hpp"
#include "objet/Entite.hpp"
#include "objet/asteroide.hpp"
#include "objet/tir.hpp"
#include "objet/player.hpp"

/**
 * @brief Prend deux entités et vérifient si il y a collision
 * 
 * @param a une entité
 * @param b une autre entité
 * @return true si il y a collision
 * @return false sinon
 */
bool isCollide(Entite *a,Entite *b)

{
  return (b->getx() - a->getx())*(b->getx() - a->getx())+
         (b->gety() - a->gety())*(b->gety() - a->gety())<
         (a->getR() + b->getR())*(a->getR() + b->getR());
}


/**
 * @brief C'est la boucle principale. Elle gère en particulier l'interaction avec le joueur et fait appel aux autres fichiers sources.
 * 
 * @return int 
 */
int main() {
// Music du menu d'accueil
sf::Music musicHub;
if (!musicHub.openFromFile("Ressources/audio/Dofus2.wav")) {
    throw std::runtime_error("Failed to load musicHub file");
}
musicHub.play();
// Création d'une fenetre pour le menu d'accueil et lancement.
sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroid Game");
TableauDesScores LeScore;
Menu menu(window, musicHub);
std::tuple <std::string, float> action = menu.run(); // On récupère les choix effectués par le joueur (mode de jeu et volume sonore)
float VolumeSelected=std::get<1>(action);
musicHub.stop();

// Chargement des effets sonores ( Faire un fichier séparé qui gère le son ?) //
// Blaster
sf::SoundBuffer shootSoundBuffer;
sf::Sound shootSound;
if (!shootSoundBuffer.loadFromFile("Ressources/audio/tir.wav")) {
    throw std::runtime_error("Failed to load shootSound");}
shootSound.setBuffer(shootSoundBuffer);
int shootVolume = 8*VolumeSelected;
shootSound.setVolume(shootVolume);
//Explosion Vaisseau
sf::SoundBuffer DeathSoundBuffer;
sf::Sound DeathSound;
if (!DeathSoundBuffer.loadFromFile("Ressources/audio/death.wav")) {
    throw std::runtime_error("Failed to load DeathSound");}
DeathSound.setBuffer(DeathSoundBuffer);
int DeathVolume = 100*VolumeSelected;
DeathSound.setVolume(DeathVolume);
// Effet sonore click bouton
sf::SoundBuffer clickSoundBuffer;
if (!clickSoundBuffer.loadFromFile("Ressources/audio/Bouton2.wav")) {
    throw std::runtime_error("Failed to load ClickSound");}
sf::Sound clickSound;
clickSound.setBuffer(clickSoundBuffer);

// Boucle de jeu en Solo //
while(std::get<0>(action) == "JouerSolo"){
    // Chargement et lancement de la musique du jeu
    sf::Music musicGame;
    if (!musicGame.openFromFile("Ressources/audio/Glory.wav")) {
        throw std::runtime_error("Failed to load musicGame");}
    int musicVolume = 70*VolumeSelected;
    musicGame.setVolume(musicVolume);
    musicGame.play();

    srand(time(0));
    // Génération de la fenetre de jeu
    sf::RenderWindow app(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroides!");
    app.setFramerateLimit(60);

    //Chargement des textures pour les animations
    sf::Texture t1,t2,t3,t4,t5,t10,t11,t12,t13,t14,t21,t22;
    try {
        if (!t1.loadFromFile("Ressources/animation/spaceship.png")) {
            throw std::runtime_error("Failed to load spaceship.png");
        }
        if (!t2.loadFromFile("Ressources/image/Space_Background.png")) {
            throw std::runtime_error("Failed to load Space_Background.png");
        }
        if (!t3.loadFromFile("Ressources/animation/explosions/type_C.png")) {
            throw std::runtime_error("Failed to load type_C.png");
        }
        if (!t4.loadFromFile("Ressources/animation/explosions/type_B.png")) {
            throw std::runtime_error("Failed to load type_B.png");
        }
        if (!t5.loadFromFile("Ressources/animation/fire_red.png")) {
            throw std::runtime_error("Failed to load fire_red.png");
        }
        if (!t10.loadFromFile("Ressources/animation/TerranWet.png")) {
            throw std::runtime_error("Failed to load TerranWet.png");
        }
        if (!t11.loadFromFile("Ressources/animation/NoAtmosphere.png")) {
            throw std::runtime_error("Failed to load NoAtmosphere.png");
        }
        if (!t12.loadFromFile("Ressources/animation/LavaPlanet.png")) {
            throw std::runtime_error("Failed to load LavaPlanet.png");
        }
        if (!t13.loadFromFile("Ressources/animation/Star.png")) {
            throw std::runtime_error("Failed to load Star.png");
        }
        if (!t14.loadFromFile("Ressources/animation/Blackhole.png")) {
            throw std::runtime_error("Failed to load Blackhole.png");
        }
        if (!t21.loadFromFile("Ressources/animation/asteroide1.png")) {
            throw std::runtime_error("Failed to load asteroide1.png");
        }
        if (!t22.loadFromFile("Ressources/animation/asteroide2.png")) {
            throw std::runtime_error("Failed to load asteroide2.png");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
    t1.setSmooth(true);
    t2.setSmooth(true);
    sf::Sprite background(t2);
    // Param : (texture, x = position de départ des images sur la texture, y = pareil en vertical,
    // w = largeur image, h = hauteur image, count = nbr d'image, speed = vitesse de transition)
    Animation sPlayer(t1, 40,0,40,40, 1, 0);
    Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animation sExplosion(t3, 0,0,256,256, 48, 0.5);
    Animation sExplosion_ship(t4, 0,0,192,192, 64, 0.5);
    Animation sBullet(t5, 0,0,32,64, 16, 0.8);
    Animation sTerranWet(t10, 0, 0, 50, 50, 50, 0.2);
    Animation sNoAtmosphere(t11, 0, 0, 50, 50, 50, 0.2);
    Animation sLavaPlanet(t12, 0, 0, 50, 50, 50, 0.2);
    Animation sStar(t13, 0, 0, 50, 50, 50, 0.2);
    Animation sBlackhole(t14, 0, 0, 50, 50, 50, 0.2);
    Animation sAsteroide1(t21, 0, 0, 50, 50, 50, 0.2);
    Animation sAsteroide2(t22, 0, 0, 50, 50, 50, 0.2);
    int asteroideWidth = 25; // à modifier en fonction de la texture choisie
    int petitAsteroideWidth = 15; // à modifier en fonction de la texture choisie


    // Création d'une liste contenant l'ensemble des entités courantes.
    std::list<Entite*> entities;

    // Génère un nombre d'astéroïdes désiré au commencement.
    for(int i=0;i<NombreAsteroideStart;i++)
    {
        asteroide *a = new asteroide();
        int NumeroTexture = std::rand() % 4;
        if (NumeroTexture == 0) {a->settings(sTerranWet, rand()%LargeurFenetre, rand()%HauteurFenetre, rand()%360, asteroideWidth);}
        else if (NumeroTexture == 1) {a->settings(sNoAtmosphere, rand()%LargeurFenetre, rand()%HauteurFenetre, rand()%360, asteroideWidth);}
        else if (NumeroTexture == 2) {a->settings(sLavaPlanet, rand()%LargeurFenetre, rand()%HauteurFenetre, rand()%360, asteroideWidth);}
        else {a->settings(sStar, rand()%LargeurFenetre, rand()%HauteurFenetre, rand()%360, petitAsteroideWidth);}
        entities.push_back(a);
    }

    // Création d'une instance player
    player *p = new player();
    p->settings(sPlayer,200,200,0,20);
    entities.push_back(p);

    // Variable pour le temps écoulé
    auto Temps_start = std::chrono::steady_clock::now();
    bool invincible = true;
    // Boucle principale du jeu qui tourne tant que le jeu est en cours. Elle gère l'affichage des entités à chaque frame //
    while (app.isOpen())
    {
        auto Temps_current = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(Temps_current - Temps_start);
        if (duration.count() >= Temps_invincible) {
            invincible = false;}
        
        /* Le code ci-dessous gère les événements. Il utilise une boucle while pour
        interroger en permanence les événements. */
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Space)
                {
                    tir *b = new tir();
                    b->settings(sBullet,p->getx(),p->gety(),p->getangle(),10);
                    entities.push_back(b);
                    shootSound.play();
                }
        }
        // Contrôles pour le déplacement du joueur
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p->setangle(p->getangle() + 3);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) p->setangle(p->getangle() - 3);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) p->thrust=true;
        else p->thrust=false;

        // Itération sur les entités pour vérifier les collisions
        for(auto a:entities)
            for(auto b:entities)
            {   
                if (a->getName()=="asteroide" && b->getName()=="tir")
                    if ( isCollide(a,b) )
                        {   // mise à false de leur vie pour une futur suppression de l'entité.
                            a->setLife(false);
                            b->setLife(false);
                            // Génère une entité avec la texture explosion à l'endroit de la collision
                            Entite *e = new Entite();
                            e->settings(sExplosion,a->getx(),a->gety());
                            e->setName("explosion");
                            entities.push_back(e);

                            // Ici le score correspond au nombre d'astéroïde détruit. 
                            LeScore.increaseScore(1);

                            // On scinde les gros astéroïdes en NombreResidu astéroïdes de petite taille. 
                            for(int i=0; i<NombreResidu; i++)
                            {
                                if (a->getR()==asteroideWidth){
                                    Entite *e = new asteroide();
                                    int NumeroTextureAsteroide = std::rand() % 2;
                                    if (NumeroTextureAsteroide == 0) {e->settings(sAsteroide1,a->getx(),a->gety(),rand()%360,petitAsteroideWidth);}
                                    else {e->settings(sAsteroide2,a->getx(),a->gety(),rand()%360,petitAsteroideWidth);}
                                    entities.push_back(e);
                                }
                            }

                        }

                    if (a->getName()=="player" && b->getName()=="asteroide" && !invincible)
                        if ( isCollide(a,b) )
                        {
                            b->setLife(false);
                            // Génère une entité avec la texture explosion à l'endroit de la collision
                            Entite *e = new Entite();
                            e->settings(sExplosion_ship,a->getx(),a->gety());
                            e->setName("explosion");
                            entities.push_back(e);
                            // Le vaisseau est détruit. La fenêtre de jeu se ferme.
                            app.close();
                            DeathSound.play();
                            musicGame.stop();
                        }
                }  

            // En fonction de l'entrée de la touche Boost, la texture du vaisseau est modifiée afin d'afficher les réacteurs.
            if (p->thrust)  p->setAnim(sPlayer_go);
            else   p->setAnim(sPlayer);


            for(auto e:entities)
                if (e->getName()=="explosion")
                if (e->getAnim()->isEnd()) e->setLife(false);

                if (rand()%150==0)
                {
                    asteroide *a = new asteroide();
                    int NumeroTexture = std::rand() % 4;
                    if (NumeroTexture == 0) {a->settings(sTerranWet, 0, rand()%HauteurFenetre, rand()%360, asteroideWidth);}
                    else if (NumeroTexture == 1) {a->settings(sNoAtmosphere, 0, rand()%HauteurFenetre, rand()%360, asteroideWidth);}
                    else if (NumeroTexture == 2) {a->settings(sLavaPlanet, 0, rand()%HauteurFenetre, rand()%360, asteroideWidth);}
                    else {a->settings(sStar, 0, rand()%HauteurFenetre, rand()%360, petitAsteroideWidth);}
                    entities.push_back(a);
                }

            for(auto i=entities.begin();i!=entities.end();)
            {
                Entite *e = *i;

                e->update();
                e->getAnim()->update();

                if (e->getLife()==false) {i=entities.erase(i); delete e;}
                else i++;
            }

    // On efface les affichages précédents puis on charge chacune des entitées courantes ainsi que le score. On affiche la fenetre.
    app.clear();
    app.draw(background);
    for(auto i:entities) i->draw(app);
    p->draw_bouclier(app, invincible);
    LeScore.drawScore(app);
    app.display();
    } // Fin boucle while app.isOpen()

    // Le joueur vient de terminer sa partie en modeSolo. Il faut maintenant afficher l'écran GameOver
    sf::RenderWindow window(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroid Game Over");
    int scoreFinal = LeScore.getScore();
    GameOverScreen gameOverScreen(scoreFinal);
    bool actionRecu = false;
    // On effectue une boucle while pour l'affichage dynamique de la fenêtre.
    while (window.isOpen() && !actionRecu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) { // Le Joueur veut rejouer
                    clickSound.play();
                    std::get<0>(action) = "JouerSolo";
                    actionRecu = true;
                    LeScore.reset();
                    std::cout << "Restarting the game..." << std::endl;}
                else if (event.key.code == sf::Keyboard::Q) { // Le Joueur veut quitter
                    clickSound.play();
                    std::get<0>(action) = "Quitter";
                    actionRecu = true;
                    std::cout << "Exiting the game..." << std::endl;
                    window.close();}
            }
        }
        // On nettoie la fenêtre puis génère les nouveaux éléments. On affiche la fenêtre.
        window.clear();
        gameOverScreen.draw(window);
        window.display();
    }
}// fin de la boucle while Action==Jouer

// Boucle de jeu en Multi
while(std::get<0>(action) == "JouerMulti"){

    // Chargement et lancement de la musique du jeu
    sf::Music musicGame;
    if (!musicGame.openFromFile("Ressources/audio/Glory.wav")) {
        throw std::runtime_error("Failed to load musicGame");}
    int musicVolume = 70*VolumeSelected;
    musicGame.setVolume(musicVolume);
    musicGame.play();

    srand(time(0));
    // Génération de la fenetre de jeu
    sf::RenderWindow app(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroides!");
    app.setFramerateLimit(60);


    //Chargement des textures pour les animations
    sf::Texture t1,t2,t3,t4,t5,t6;
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
    Animation sBulletRed(t5, 0,0,32,64, 16, 0.8);
    Animation sBulletBlue(t6, 0,0,32,64, 16, 0.8);
    Animation sPlayer1(t1, 40,0,40,40, 1, 0);
    Animation sPlayer2(t3, 40,0,40,40, 1, 0);
    Animation sPlayer1_go(t1, 40,40,40,40, 1, 0);
    Animation sPlayer2_go(t3, 40,40,40,40, 1, 0);
    Animation sExplosion_ship(t4, 0,0,192,192, 64, 0.5);


    // Création d'une liste contenant l'ensemble des entités courantes.
    std::list<Entite*> entities;

    // Création des deux instances player
    player *p1 = new player();
    p1->setTeam(1);
    p1->settings(sPlayer1,LargeurFenetre-200,HauteurFenetre-200,180,20);
    entities.push_back(p1);

    player *p2 = new player();
    p2->setTeam(2);
    p2->settings(sPlayer2,200,200,0,20);
    entities.push_back(p2);

    int gagnant = -1; // Permet de récupérer l'équipe victorieuse


    // Boucle principale du jeu qui tourne tant que le jeu est en cours. Elle gère l'affichage des entités à chaque frame ///
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                app.close();}

            if (event.type == sf::Event::KeyPressed)
                {
                if (event.key.code == sf::Keyboard::SemiColon)
                {   //Tir du joueur 1
                    tir *t1 = new tir();
                    t1->setTeam(1);
                    t1->settings(sBulletRed,p1->getx(),p1->gety(),p1->getangle(),10);
                    entities.push_back(t1);
                    shootSound.play();
                }
                if (event.key.code == sf::Keyboard::X)
                {   //Tir du joueur 2
                    tir *t2 = new tir();
                    t2->setTeam(2);
                    t2->settings(sBulletBlue,p2->getx(),p2->gety(),p2->getangle(),10);
                    entities.push_back(t2);
                    shootSound.play();
                }
            }
        }

        // Contrôles du joueur 1
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {p1->setangle(p1->getangle() + 3);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {p1->setangle(p1->getangle() - 3);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {p1->thrust=true;}
        else {p1->thrust=false;}
        // Contrôles du joueur 2
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {p2->setangle(p2->getangle() + 3);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {p2->setangle(p2->getangle() - 3);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {p2->thrust=true;}
        else {p2->thrust=false;}


        for(auto a:entities)
        {
            for(auto b:entities)
            {
                if (a->getName()=="player" && b->getName()=="tir")
                {
                    if (isCollide(a,b) && a->getTeam()!=b->getTeam())
                    {
                        b->setLife(false);
                        a->setLife(false);

                        Entite *e = new Entite();
                        e->settings(sExplosion_ship,a->getx(),a->gety());
                        e->setName("explosion");
                        entities.push_back(e);

                        app.close();
                        DeathSound.play();
                        musicGame.stop();

                        gagnant = b->getTeam();
                    }
                }
            }//fin for b:entities
        }

        // En fonction de l'entrée de la touche Boost, la texture du vaisseau est modifiée afin d'afficher les réacteurs.
        if (p1->thrust)  p1->setAnim(sPlayer1_go);
        else   p1->setAnim(sPlayer1);
        if (p2->thrust)  p2->setAnim(sPlayer2_go);
        else   p2->setAnim(sPlayer2);

        // Les explosions n'ont qu'une seule apparition. Une fois généré, elles sont immédiatement supprimées.
        for(auto e:entities)
            if (e->getName()=="explosion")
            if (e->getAnim()->isEnd()) e->setLife(0);


        /* Le code ci-dessus parcourt un conteneur appelé « entités ». Il met à jour 
        chaque entité du conteneur. Si la variable « vie » d'une entité est fausse, elle est
        supprimée du conteneur et est supprimée. */
        for(auto i=entities.begin();i!=entities.end();)
        {
            Entite *e = *i;

            e->update();
            e->getAnim()->update();

            if (e->getLife()==false) {i=entities.erase(i); delete e;}
            else i++;
        }

        // On nettoie la fenêtre puis affiche les entitées courantes.
        app.clear();
        app.draw(background);
        for(auto i:entities) i->draw(app);
        app.display();

    }//fin while app.isOpen()

    // Un des vaisseaux est détruit. Le gagnant peut admirer la preuve de sa victoire sur l'écran GameOver
    sf::RenderWindow window(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroid Game Over");
    GameOverMultiScreen gameOverMultiScreen(gagnant);
    bool actionRecu = false;
    // On effectue une boucle while pour avoir une fenêtre interactive à travers les entrées claviers.
    while (window.isOpen() && !actionRecu)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    clickSound.play();
                    std::get<0>(action) = "JouerMulti";
                    actionRecu = true;
                    std::cout << "Restarting the game..." << std::endl;}
                else if (event.key.code == sf::Keyboard::Q) {
                    clickSound.play();
                    std::get<0>(action) = "Quitter";
                    actionRecu = true;
                    std::cout << "Exiting the game..." << std::endl;
                    window.close();}
            }
        }
        // Nettoyage de la fenêtre et affichage des nouveaux éléments.
        window.clear();
        gameOverMultiScreen.draw(window);
        window.display();
    }
}// fin de la boucle while Action==JouerMulti

// ! Les 2 modes ont beaucoup de code en commun. Une optimisation est certainement possible. Une partie du code pourrait être contenu directement dans le fichier source GameOver et GameOverMulti. Ces deux interfaces pourraient dérivées d'une même classe de base.

return 0;
}
