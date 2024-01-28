#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include<math.h>
#include<time.h>


sf::Color normalColor = sf::Color::White;
sf::Color hoverColor = sf::Color(200, 200, 200); // Couleur gris clair pour simuler le survol

const int LargeurFenetre = 1200;
const int HauteurFenetre = 800;

float DEGTORAD = 0.017453f;

class GameOverScreen {
private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text retryText;
    sf::Text quitText;

public:
    GameOverScreen() {
        if (!font.loadFromFile("../Ressources/police/arial/arial.ttf")) {
        }

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("Game Over");
        gameOverText.setPosition((LargeurFenetre - gameOverText.getGlobalBounds().width) / 2, HauteurFenetre/2 - 50);

        retryText.setFont(font);
        retryText.setCharacterSize(30);
        retryText.setFillColor(sf::Color::White);
        retryText.setString("Press R to Retry");
        retryText.setPosition((LargeurFenetre - retryText.getGlobalBounds().width) / 2, HauteurFenetre/2 + 50);

        quitText.setFont(font);
        quitText.setCharacterSize(30);
        quitText.setFillColor(sf::Color::White);
        quitText.setString("Press Q to Quit");
        quitText.setPosition((LargeurFenetre - quitText.getGlobalBounds().width) / 2, HauteurFenetre/2 + 100);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(gameOverText);
        window.draw(retryText);
        window.draw(quitText);
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroid Game");
    GameOverScreen gameOverScreen;


    sf::SoundBuffer DeathSoundBuffer;
    sf::Sound DeathSound;
    if (!DeathSoundBuffer.loadFromFile("../Ressources/audio/death.wav")) {
    std::cerr << "Failed to load death sound file" << std::endl;}
    DeathSound.setBuffer(DeathSoundBuffer);
    int DeathVolume = 5;
    DeathSound.setVolume(DeathVolume);


    /// MAIN LOOP ///
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    // Code pour redémarrer le jeu
                    std::cout << "Restarting the game..." << std::endl;
                } else if (event.key.code == sf::Keyboard::Q) {
                    window.close();
                }
            }
        }

        window.clear();
        gameOverScreen.draw(window);
        window.display();
    }

    return 0;
}