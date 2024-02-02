                                            /// Bibliothèques ///
#include "TableauDesScores.hpp"
#include "global_variables.hpp"                            

                                            /// Code Principal ///

void TableauDesScores::increaseScore(int points) {score += points;}

void TableauDesScores::drawScore(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Ressources/police/arial/arial.ttf")) {
        // Gérer l'erreur de chargement de la police
        std::cerr << "Failed to load font file" << std::endl;
        return;
    }
    sf::Text scoreText("Score: " + std::to_string(score), font, 30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    window.draw(scoreText); // Dessiner le compteur de points à l'écran
}

void TableauDesScores::reset(){score = 0;}

int TableauDesScores::getScore(){return score;}

