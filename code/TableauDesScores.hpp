#ifndef TABLEAUDESSCORES_HPP
#define TABLEAUDESSCORES_HPP
                                            /// Bibliothéques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

                                            /// Code Principal ///
class TableauDesScores {
    private:
        int score;

    public:
        TableauDesScores() : score(0) {} // Initialiser le compteur de points à zéro

        void increaseScore(int points);

        void drawScore(sf::RenderWindow& window);

        void reset();

        int getScore();
};

#endif // TABLEAUDESSCORES_HPP