#ifndef TABLEAUDESSCORES_HPP
#define TABLEAUDESSCORES_HPP
                                            // Bibliothéques //
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

                                            // Code Principal //
/**
 * @brief Classe représentant un tableau des scores.
 * 
 * Cette classe gère un tableau des scores dans le jeu, permettant d'incrémenter le score,
 * de le réinitialiser et de le dessiner sur une fenêtre SFML.
 */
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