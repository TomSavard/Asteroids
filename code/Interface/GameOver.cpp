/**
 * Le code ci-dessous définit une classe GameOverScreen en C++ qui affiche un jeu sur écran avec le
 * score et les options pour redémarrer ou quitter le jeu.
 * 
 * @param score Le paramètre « score » est un nombre entier qui représente le score du joueur dans la
 * partie.
 */
                                            // Bibliothèques //
#include "GameOver.hpp"     
#include "../global_variables.hpp"                             

                                            // Code Principal //

/**
 * @brief Constructeur de la classe GameOverScreen.
 * 
 * Initialise l'écran de fin de jeu avec le score fourni et configure les éléments d'affichage.
 * 
 * @param score Le score du joueur à afficher.
 * 
 * @note Ce constructeur suppose que le fichier de police Arial est disponible dans le répertoire des ressources.
 */
GameOverScreen::GameOverScreen(int score) {

    if (!font.loadFromFile("Ressources/police/arial/arial.ttf")) {
    }

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition((LargeurFenetre - gameOverText.getGlobalBounds().width) / 2, HauteurFenetre/2 - 100);

    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: " + std::to_string(score)); // Convertir le score en chaîne de caractères
    scoreText.setPosition((LargeurFenetre - scoreText.getGlobalBounds().width) / 2, HauteurFenetre / 2);

    retryText.setFont(font);
    retryText.setCharacterSize(30);
    retryText.setFillColor(sf::Color::White);
    retryText.setString("Appuyer sur R pour redemarrer");
    retryText.setPosition((LargeurFenetre - retryText.getGlobalBounds().width) / 2, HauteurFenetre/2 + 50);

    quitText.setFont(font);
    quitText.setCharacterSize(30);
    quitText.setFillColor(sf::Color::White);
    quitText.setString("Appuyer sur Q pour quitter");
    quitText.setPosition((LargeurFenetre - quitText.getGlobalBounds().width) / 2, HauteurFenetre/2 + 100);
}

/**
 * @brief Dessine l'écran de fin de jeu sur la fenêtre spécifiée.
 * 
 * Cette méthode dessine les différents éléments de l'écran de fin de jeu (texte de fin de partie,
 * score, instructions pour redémarrer ou quitter) sur la fenêtre spécifiée.
 * 
 * @param window La fenêtre SFML sur laquelle dessiner l'écran de fin de jeu.
 */
void GameOverScreen::draw(sf::RenderWindow &window) {
    window.draw(gameOverText);
    window.draw(scoreText);
    window.draw(retryText);
    window.draw(quitText);
}


