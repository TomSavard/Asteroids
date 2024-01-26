/// Tom SAVARD 26/01/24 ///
// * Better comments
// Command to run scripts : g++ -std=c++17 -c Fusion.cpp -I/usr/local/include
// g++ Fusion.o -o Fusion.exe -lsfml-network -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
// ./Game.exe
// ! Not to do
// ? interrogation
// TODO : 

//// Fusionner le Hub avec le jeu
// TODO : Continuer physique du jeu avec tuto yt

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory> // Ajoutez cette directive d'inclusion pour std::make_unique


// Définir la couleur normale et la couleur survolée des boutons
sf::Color normalColor = sf::Color::White;
sf::Color hoverColor = sf::Color(200, 200, 200); // Couleur gris clair pour simuler le survol



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
    // Tire des projectiles
    void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles) {
        projectiles.push_back(std::unique_ptr<Projectile>(new Projectile(position + sf::Vector2f(0.f, -50.f))));
    }
        //???
    void setPosition(sf::Vector2f pos) {
        position = pos;
    }

};

class Asteroid
{

};


// Pour les fenetres
class Menu {
public:
    enum class ActionMenu {
        Quitter,
        Jouer
    };
    Menu(sf::RenderWindow& window, sf::Music& music) : window(window), music(music) {}

    ActionMenu run() {
        sf::Font font;
        if (!font.loadFromFile("../Ressources/police/arial/arial.ttf")) {
            std::cerr << "Failed to load font." << std::endl;
            return ActionMenu::Quitter;
        }

        sf::Text title("Asteroid Game", font, 50);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold);
        title.setPosition(200, 100);

        sf::Text playButton("Play", font, 30);
        playButton.setFillColor(sf::Color::White);
        playButton.setPosition(300, 250);

        sf::Text exitButton("Exit", font, 30);
        exitButton.setFillColor(sf::Color::White);
        exitButton.setPosition(300, 350);

        sf::RectangleShape volumeBar(sf::Vector2f(200, 20));
        volumeBar.setFillColor(sf::Color(200, 200, 200)); // Couleur gris clair
        volumeBar.setPosition(window.getSize().x - 250, window.getSize().y - 50);

        sf::CircleShape volumeIndicator(10);
        volumeIndicator.setFillColor(sf::Color::White);
        volumeIndicator.setOutlineColor(sf::Color::Black);
        volumeIndicator.setOutlineThickness(2);
        volumeIndicator.setOrigin(5, 5);
        volumeIndicator.setPosition(window.getSize().x - 250 + volume * 200, window.getSize().y - 45);

        bool isDragging = false;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (playButton.getGlobalBounds().contains(mousePos)) {
                        // Action lorsque le bouton "Jouer" est cliqué
                        std::cout << "Bouton Jouer cliqué" << std::endl;
                        window.close(); // Fermer la fenêtre lorsque le bouton "Jouer" est cliqué
                        return ActionMenu::Jouer;
                    }
                    else if (exitButton.getGlobalBounds().contains(mousePos)) {
                        // Action lorsque le bouton "Quitter" est cliqué
                        std::cout << "Bouton quitter cliqué!" << std::endl;
                        window.close(); // Fermer la fenêtre lorsque le bouton "Quitter" est cliqué
                        return ActionMenu::Quitter;
                    }
                    else if (volumeIndicator.getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                    }
                } 
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    isDragging = false;
                } 
                else if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    // Gestion du survol des boutons
                    if (playButton.getGlobalBounds().contains(mousePos)) {playButton.setFillColor(hoverColor);} 
                    else {playButton.setFillColor(normalColor);}
                    if (exitButton.getGlobalBounds().contains(mousePos)) {exitButton.setFillColor(hoverColor);}
                    else {exitButton.setFillColor(normalColor);}
                    // Déplacement du bouton de volume si l'utilisateur est en train de le glisser
                    if (isDragging) {
                        float newVolume = (mousePos.x - (window.getSize().x - 250)) / 200.0f;
                        if (newVolume < 0)
                            newVolume = 0;
                        else if (newVolume > 1)
                            newVolume = 1;
                        volume = newVolume;
                        music.setVolume(volume * 100); // Réglez le volume sur une échelle de 0 à 100
                        volumeIndicator.setPosition(window.getSize().x - 250 + volume * 200, window.getSize().y - 45);
                    }
                }
            }
            window.clear();
            window.draw(title);
            window.draw(playButton);
            window.draw(exitButton);
            window.draw(volumeBar);
            window.draw(volumeIndicator);
            window.display();
        }
    return ActionMenu::Quitter;
    }

private:
    sf::RenderWindow& window;
    sf::Music& music;
    float volume = 0.5f; // Volume initial
};

class GameLauncher {
public:
    GameLauncher(sf::RenderWindow& window) : window(window) {}

void launch() {
    sf::RenderWindow window (sf::VideoMode(800,800), "Asteroid Game");
    Player joueur1(sf::Vector2f(400.f, 400.f));
    float speed = 0.5f; //vitesse du joueur
        std::vector<std::unique_ptr<Projectile>> projectiles;
        sf::Clock clock; // Horloge pour mesurer le temps écoulé

    // Boucle principale :
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type ==sf::Event::Closed) window.close();}
        sf::Time dt = clock.restart(); // Mesurer le temps écoulé depuis la dernière itération
        joueur1.update(dt, projectiles); // Mettre à jour le joueur avec le temps écoulé
        // On gère le déplacement droite/gauche/bas/haut avec les flèches directionnelles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && joueur1.getPosition().x > 20) {joueur1.move(sf::Vector2f(-speed, 0.f));}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && joueur1.getPosition().x < window.getSize().x - 20) {joueur1.move(sf::Vector2f(speed, 0.f));}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && joueur1.getPosition().y > 0) {joueur1.move(sf::Vector2f(0.f,-speed));}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && joueur1.getPosition().y < window.getSize().y - 40) {joueur1.move(sf::Vector2f(0.f,speed));}
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
}

private:
    sf::RenderWindow& window;
};


int main() {
    sf::Music musicHub;
    if (!musicHub.openFromFile("../Ressources/audio/Dofus2.wav")) {std::cerr << "Failed to load music file" << std::endl; return -1;}
    musicHub.play();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroid Game");
    Menu menu(window, musicHub);
    Menu::ActionMenu action = menu.run();

    musicHub.stop();

    if (action == Menu::ActionMenu::Jouer) {
        sf::Music musicGame;
        if (!musicGame.openFromFile("../Ressources/audio/Glory.wav")) {std::cerr << "Failed to load music file" << std::endl; return -1;}
        musicGame.play();
        GameLauncher gameLauncher(window);
        gameLauncher.launch();
    }

    return 0;
}