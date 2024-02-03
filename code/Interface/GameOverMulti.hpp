#ifndef GAMEOVERMULTI_HPP
#define GAMEOVERMULTI_HPP
                                            /// Bibliothéques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

                                            /// Code Principal ///
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