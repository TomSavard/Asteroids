#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP
                                            /// Bibliothéques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

                                            /// Code Principal ///
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