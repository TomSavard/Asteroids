#include <SFML/Network.hpp>
#include <chrono> 
#include <thread> 


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

// Il y a la possibilité de séparer chaque client sur un thread différent. Cela permet une meilleur modularité et scalability.
// Cependant, il va y avoir plus de complexité sur la gestions des concurrences et sur la synchronisation.
// On commence par un unique thread et on avise en fonction des perfs.

                                // Les Fonctions
bool isCollide(Entite *a,Entite *b)

{
  return (b->getx() - a->getx())*(b->getx() - a->getx())+
         (b->gety() - a->gety())*(b->gety() - a->gety())<
         (a->getR() + b->getR())*(a->getR() + b->getR());
}

void printBoolVector(std::vector<bool> myVector){
    std::cout << "Contenu du vecteur de booléens : ";
    for (bool b : myVector) {
        std::cout << std::boolalpha << b << " ";
    }
    std::cout << std::endl;
}



std::string sendPlayerData(Entite UneEntite){
    // animation is fixed so don't need to send it
    // same for radius
    // should add the thrust
    std::string toSendX = std::to_string(UneEntite.getx());
    std::string toSendY = std::to_string(UneEntite.gety());
    std::string toSendVx = std::to_string(UneEntite.getvx());
    std::string toSendVy = std::to_string(UneEntite.getvy());
    std::string  toSendAngle= std::to_string(UneEntite.getangle());
    std::string  toSendLife= std::to_string(UneEntite.getLife());
    return "player "+ toSendX + " " + toSendY + " " + toSendVx + " " + toSendVy + " " + toSendAngle + " " + toSendLife;
}

// std::string sendPlayerData(player joueur){
//     // animation is fixed so don't need to send it
//     // same for radius
//     // should add the thrust
//     std::string toSendX = std::to_string(joueur.getx());
//     std::string toSendY = std::to_string(joueur.gety());
//     std::string toSendVx = std::to_string(joueur.getvx());
//     std::string toSendVy = std::to_string(joueur.getvy());
//     std::string  toSendAngle= std::to_string(joueur.getangle());
//     std::string  toSendLife= std::to_string(joueur.getLife());
//     return "player" + toSendX + " " + toSendY + " " + toSendVx + " " + toSendVy + " " + toSendAngle + " " + toSendLife;
// }

std::string sendTirData(Entite UneEntite){
    // animation is fixed so don't need to send it
    // same for radius
    // should add the thrust
    std::string toSendX = std::to_string(UneEntite.getx());
    std::string toSendY = std::to_string(UneEntite.gety());
    std::string toSendVx = std::to_string(UneEntite.getvx());
    std::string toSendVy = std::to_string(UneEntite.getvy());
    std::string  toSendAngle= std::to_string(UneEntite.getangle());
    std::string  toSendLife= std::to_string(UneEntite.getLife());
    return "tir "+ toSendX + " " + toSendY + " " + toSendVx + " " + toSendVy + " " + toSendAngle + " " + toSendLife;
}

int NombreClient;



int main(){

                // ETABLISSEMENT DE LA CONNEXION SERVEUR/CLIENT
std::cout << "Combien de client souhaitez vous ? (int): ";
std::cin >> NombreClient;
if (std::cin.fail()) {
    std::cerr << "Erreur valeur, veuillez entrer un entier." << std::endl;
    return -1;
}

sf::TcpListener listener;

// bind the listener to a port
if (listener.listen(53000) != sf::Socket::Done)
{
    std::cerr << "Failed to bind port for listening!" << std::endl;
    return 1;
}
else { std::cout << "Now listening to port 53000" << std::endl;}

// Vecteur pour stocker les clients acceptés
std::vector<std::unique_ptr<sf::TcpSocket>> clients;

for (int i=0; i<NombreClient; i++){
// accept a new connection
    std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket());
    if (listener.accept(*client) != sf::Socket::Done)
    {
        std::cerr << "Failed to accept incoming connection!" << std::endl;
        return 1;
    }
    else { std::cout << "Client numéro " << i <<  " connecté" << std::endl;} 

    // Stocker le client dans le vecteur
    clients.push_back(std::move(client));
}






// Boucle de jeu en Solo //
while(true){

    // Génération de la fenetre de jeu
    sf::RenderWindow app(sf::VideoMode(200, 200), "Serveur");
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
//!
    player *p2 = new player();
    p2->setTeam(2);
    p2->settings(sPlayer2,200,200,0,20);
    entities.push_back(p2);

    int gagnant = -1; // Permet de récupérer l'équipe victorieuse


    sf::Event event;
    while (app.isOpen())
    {
                std::vector<sf::Packet> packets;

        // RÉCUPÉRATION DES DONNÉES CLIENTS
        std::string message;
        for (size_t i= 0; i < clients.size() ; i++) {
            auto& clientPtr=clients[i];
            sf::Packet packet;
            clientPtr->setBlocking(false);
            sf::Socket::Status status = clientPtr->receive(packet);
            if (status == sf::Socket::Done) {
                if (packet >> message) {
                    std::cout << "Client " << i <<" : " << message << std::endl;
                } else {
                    std::cerr << "Erreur lors de l'extraction du message du paquet !" << std::endl;
                }
            } else if (status == sf::Socket::NotReady) {
                // Pas de données disponibles, continuer avec le prochain client
                continue;
            } else {
                // Erreur lors de la réception des données
                std::cout << "Déconnection du client numéro "<< i << std::endl;
                return 1;
            }
        }

        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                app.close();}
            if (message[0] == '1')
            {   //Tir du joueur 1
                tir *t1 = new tir();
                t1->setTeam(1);
                t1->settings(sBulletRed,p1->getx(),p1->gety(),p1->getangle(),10);
                entities.push_back(t1);
            }
            //!
            if (message[0] == 1)
            {   //Tir du joueur 2
                tir *t2 = new tir();
                t2->setTeam(2);
                t2->settings(sBulletBlue,p2->getx(),p2->gety(),p2->getangle(),10);
                entities.push_back(t2);
            }
        }

        // Contrôles du joueur 1
        if(message[1] == '1') {p1->setangle(p1->getangle() + 6);}
        if(message[2] == '1') {p1->setangle(p1->getangle() - 6);}
        if(message[3] == '1') {p1->thrust=true;}
        else {p1->thrust=false;}
//!        // // Contrôles du joueur 2
        if(message[1] == '1') {p2->setangle(p2->getangle() + 6);}
        if(message[2] == '1') {p2->setangle(p2->getangle() - 6);}
        if(message[3] == '1') {p2->thrust=true;}
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

        // Ils faut envoyer les entités courantes aux clients pour qu'ils puissent les afficher
        for(auto i:entities){
        // Envoyer un message à tous les clients connectés
        //!
        // if (i->getName() == "tir"){std::string message = sendTirData(*i);}
        std::string message = sendPlayerData(*i);
        sf::Packet packet;
        packet << message;
        for (size_t i = 0; i < clients.size(); ++i) {
            // if (clients[i]->send(packet) != sf::Socket::Done) {
            //     std::cerr << "Erreur lors de l'envoi du message au client " << i << std::endl;
            //     // Gérer l'erreur et déconnecter le client si nécessaire
            // }
            clients[i]->send(packet);
        }
        }

    }//fin while app.isOpen()


}



return 0;
}