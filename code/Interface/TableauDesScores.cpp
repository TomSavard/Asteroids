/**
 * Le code définit une classe appelée "TableauDesScores" qui gère un compteur de scores et fournit des
 * fonctions pour augmenter, afficher, réinitialiser et récupérer le score.
 * 
 * @param points Le paramètre « points » est un nombre entier qui représente le nombre de points à
 * ajouter au score.
 */
                                            // Bibliothèques //
#include "TableauDesScores.hpp"
#include "../global_variables.hpp"                            

                                            // Code Principal //
/**
 * @brief Incrémente le score de la valeur spécifiée.
 * 
 * @param points La valeur à ajouter au score actuel.
 */
void TableauDesScores::increaseScore(int points) {score += points;}

/**
 * @brief Dessine le score sur la fenêtre spécifiée.
 * 
 * Cette méthode dessine le score actuel sur la fenêtre SFML spécifiée.
 * 
 * @param window La fenêtre SFML sur laquelle dessiner le score.
 */
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

/**
 * @brief Réinitialise le score à zéro.
 * 
 * Cette méthode réinitialise le score à zéro, remettant ainsi le compteur de points à sa valeur initiale.
 */
void TableauDesScores::reset(){score = 0;}

/**
 * @brief Obtient le score actuel.
 * 
 * @return Le score actuel.
 */
int TableauDesScores::getScore(){return score;}

