#include <SFML/Network.hpp>
#include <iostream>
#include <chrono> 
#include <thread> 
#include <vector>
#include <memory>

// Il y a la possibilité de séparer chaque client sur un thread différent. Cela permet une meilleur modularité et scalability.
// Cependant, il va y avoir plus de complexité sur la gestions des concurrences et sur la synchronisation.
// On commence par un unique thread et on avise en fonction des perfs.

void printBoolVector(std::vector<bool> myVector){
    std::cout << "Contenu du vecteur de booléens : ";
    for (bool b : myVector) {
        std::cout << std::boolalpha << b << " ";
    }
    std::cout << std::endl;
}

int NombreClient = 2;

int main(){

    std::cout << "Combien de client souhaitez vous ? (int): ";

    // get input
    std::cin >> NombreClient;

    // check and see if the input statement succeeded
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

while(true){

std::vector<sf::Packet> packets;

// RÉCUPÉRATION DES DONNÉES CLIENTS
for (size_t i= 0; i < clients.size() ; i++) {
    auto& clientPtr=clients[i];
    sf::Packet packet;
    clientPtr->setBlocking(false);
    sf::Socket::Status status = clientPtr->receive(packet);
    if (status == sf::Socket::Done) {
        
        std::string message;
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


// Effacer les paquets reçus pour éviter de les traiter à nouveau lors de la prochaine itération
packets.clear();

}


return 0;
}