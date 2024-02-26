#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <memory> // Pour std::unique_ptr

int main() {
    // Création du listener
    sf::TcpListener listener;
    if (listener.listen(53000) != sf::Socket::Done) {
        std::cerr << "Erreur lors de l'écoute sur le port 53000" << std::endl;
        return 1;
    }

    std::cout << "Le serveur écoute sur le port 53000..." << std::endl;

    // Vector pour stocker les clients connectés
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;

    // Boucle d'attente de connexion
    while (true) {
        // Attente d'une connexion
        std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket);
        if (listener.accept(*client) != sf::Socket::Done) {
            std::cerr << "Erreur lors de la connexion d'un client" << std::endl;
            continue; // Continuer à attendre les connexions
        }

        std::cout << "Client connecté : " << client->getRemoteAddress() << std::endl;

        // Ajouter le client à la liste des clients connectés
        clients.push_back(std::move(client));

        // Créer un thread ou un processus pour gérer ce client, si nécessaire
    }

    return 0;
}
