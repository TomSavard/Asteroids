#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP
                                            // Bibliothéques //
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

                                            // Code Principal //
/**
 * @brief Classe représentant l'écran de fin de jeu.
 * 
 * Cette classe gère l'affichage de l'écran de fin de jeu, incluant le message de fin de partie,
 * le score du joueur, ainsi que les instructions pour redémarrer ou quitter le jeu.
 */
class GameOverScreen {
private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text retryText;
    sf::Text quitText;
    sf::Text scoreText;

public:
    GameOverScreen(int score =0);

    void draw(sf::RenderWindow &window);
};

#endif // GAMEOVER_HPP