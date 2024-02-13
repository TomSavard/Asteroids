#ifndef GAMEOVERMULTI_HPP
#define GAMEOVERMULTI_HPP
                                            // Bibliothéques //
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

                                            // Code Principal //
/**
 * @brief Classe représentant l'écran de fin de jeu multijoueur.
 * 
 * Cette classe gère l'affichage de l'écran de fin de jeu multijoueur, incluant le message de fin de partie,
 * le nom du joueur gagnant, ainsi que les instructions pour redémarrer ou quitter le jeu.
 */
class GameOverMultiScreen {
private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text retryText;
    sf::Text quitText;
    sf::Text gagnantText;

public:
    GameOverMultiScreen(int gagnant);

    void draw(sf::RenderWindow &window);
};

#endif // GAMEOVERMULTI_HPP