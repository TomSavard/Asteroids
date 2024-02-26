#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main() {
    // Connexion au serveur
    sf::TcpSocket socket;
    if (socket.connect("127.0.0.1", 53000) != sf::Socket::Done) {
        std::cerr << "Erreur lors de la connexion au serveur" << std::endl;
        return 1;
    }

    std::cout << "Connecté au serveur !" << std::endl;

    // Boucle principale pour l'échange de messages
    while (true) {
        // Envoi d'un message au serveur
        std::string message;
        std::cout << "Entrez un message : ";
        std::getline(std::cin, message);
        sf::Packet packet;
        packet << message;
        if (socket.send(packet) != sf::Socket::Done) {
            std::cerr << "Erreur lors de l'envoi du message au serveur" << std::endl;
            break;
        }

        // Réception de la réponse du serveur
        sf::Packet replyPacket;
        if (socket.receive(replyPacket) != sf::Socket::Done) {
            std::cerr << "Erreur lors de la réception de la réponse du serveur" << std::endl;
            break;
        }

        std::string replyMessage;
        replyPacket >> replyMessage;
        std::cout << "Réponse du serveur : " << replyMessage << std::endl;
    }

    // Fermeture de la connexion
    socket.disconnect();

    return 0;
}
