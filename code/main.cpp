#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>



// Les différentes classes d'objets :
class Projectile {
public:
    Projectile(sf::Vector2f position) : shape(sf::Vector2f(5.f, 5.f)), lifetime(sf::Time::Zero) {
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    void update(sf::Time dt) {
    sf::Vector2f velocity(0.f, -200.f); // Vitesse du projectile
    shape.move(velocity * dt.asSeconds()); // Mettre à jour la position du projectile en fonction de la vitesse
    lifetime += dt; // Mettre à jour la durée de vie du projectile
    }

    bool isExpired() const {
        return lifetime >= maxLifetime; // Vérifier si la durée de vie dépasse la limite
    }

private:
    sf::RectangleShape shape;
        sf::Time lifetime;
    const sf::Time maxLifetime = sf::seconds(5.f); // Durée de vie maximale du projectile
};

class Player
{
friend class Projectile; // Déclaration d'amitié

private:
    sf::Vector2f position;
    sf::Time shootTimer;
    sf::ConvexShape shape;
    const sf::Time shootCooldown = sf::seconds(0.3f); // Cooldown entre deux tirs

public:

// Constructeur 
Player(sf::Vector2f startPos) : position(startPos), shootTimer(sf::seconds(0.f)) {
    shape.setPointCount(4);
    shape.setPoint(0, sf::Vector2f(0, 0));
    shape.setPoint(1, sf::Vector2f(20, 40));
    shape.setPoint(2, sf::Vector2f(0, 30));
    shape.setPoint(3, sf::Vector2f(-20, 40));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(startPos);
}

void update(sf::Time dt, std::vector<std::unique_ptr<Projectile>>& projectiles) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer >= shootCooldown) {
        shoot(projectiles);
        shootTimer = sf::Time::Zero; // Réinitialiser la minuterie de tir
    }
    // Mettre à jour la minuterie de tir
    shootTimer += dt;
}


//Les différentes fonctions de player
        //Le déplacement
    void move(sf::Vector2f offset) {
        position += offset;
        shape.move(offset);
    }

        //lire sa position
    sf::Vector2f getPosition() const {
        return position;
    }
        //l'affichage du vaisseau
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }
        //tire des projectiles
    void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles) {
        projectiles.push_back(std::make_unique<Projectile>(position + sf::Vector2f(0.f, -50.f)));
    }
        //???
    void setPosition(sf::Vector2f pos) {
        position = pos;
    }

};

class Asteroid
{

};



int main()
{

// Créer une fenetre :
sf::RenderWindow window (sf::VideoMode(800,800), "Asteroid Game");


// Créer une instance de Player nommé joueur 1
Player joueur1(sf::Vector2f(400.f, 400.f));
float speed = 0.5f;

std::vector<std::unique_ptr<Projectile>> projectiles;


sf::Clock clock; // Horloge pour mesurer le temps écoulé


// Charge(plutot stream) et joue la musique
// sf::Music music;
// if (!music.openFromFile("../Ressources/audio/Glory.wav")) {
//     std::cerr << "Failed to load music file" << std::endl;
//     return -1; // Error
// }
// music.play();



// Boucle principale :
while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type ==sf::Event::Closed)
        window.close();
    }

    sf::Time dt = clock.restart(); // Mesurer le temps écoulé depuis la dernière itération
    joueur1.update(dt, projectiles); // Mettre à jour le joueur avec le temps écoulé


    // On gère le déplacement droite/gauche/bas/haut avec les flèches directionnelles
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && joueur1.getPosition().x > 20) {
            joueur1.move(sf::Vector2f(-speed, 0.f));
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && joueur1.getPosition().x < window.getSize().x - 20) {
            joueur1.move(sf::Vector2f(speed, 0.f));
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && joueur1.getPosition().y > 0) {
            joueur1.move(sf::Vector2f(0.f,-speed));
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && joueur1.getPosition().y < window.getSize().y - 40) {
            joueur1.move(sf::Vector2f(0.f,speed));
        }

    // Vérifie si la touche "espace" est enfoncée pour tirer un projectile
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        joueur1.update(dt, projectiles);
    }




    // Netoyyage de la fenetre
    window.clear();


    // Mettre à jour et dessiner les projectiles
    for (auto& projectile : projectiles) {
        projectile->update(dt); // Mettre à jour la position du projectile
        projectile->draw(window); // Dessiner le projectile mis à jour
    }

    joueur1.draw(window);

// Supprimer les projectiles expirés
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
    [](const std::unique_ptr<Projectile>& p) { return p->isExpired(); }), projectiles.end());


    window.display();
    
}


    return 0;
}