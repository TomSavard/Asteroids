                                            // Bibliothèques //
#include "GameOverMulti.hpp"     
#include "../global_variables.hpp"                             

                                            // Code Principal //

/**
 * @brief Constructeur de la classe GameOverMultiScreen.
 * 
 * Initialise l'écran de fin de jeu multijoueur avec le gagnant spécifié et configure les éléments d'affichage.
 * 
 * @param gagnant Le numéro du joueur gagnant. Si égal à 1, le joueur 1 (équipe rouge) est le gagnant, sinon le joueur 2 (équipe bleue) est le gagnant.
 * 
 * @note Ce constructeur suppose que le fichier de police Arial est disponible dans le répertoire des ressources.
 */
GameOverMultiScreen::GameOverMultiScreen(int gagnant) {

    if (!font.loadFromFile("Ressources/police/arial/arial.ttf")) {
    }

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition((LargeurFenetre - gameOverText.getGlobalBounds().width) / 2, HauteurFenetre/2 - 100);

    gagnantText.setFont(font);
    gagnantText.setCharacterSize(30);
    gagnantText.setFillColor(sf::Color::White);
    if (gagnant == 1) {gagnantText.setString("Victoire du Joueur 1 (Equipe Rouge)");}
    else {gagnantText.setString("Victoire du Joueur 2 (Equipe Bleue)");}
    gagnantText.setPosition((LargeurFenetre - gagnantText.getGlobalBounds().width) / 2, HauteurFenetre / 2);

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
 * @brief Dessine l'écran de fin de jeu multijoueur sur la fenêtre spécifiée.
 * 
 * Cette méthode dessine les différents éléments de l'écran de fin de jeu multijoueur (texte de fin de partie,
 * texte indiquant le gagnant, instructions pour redémarrer ou quitter) sur la fenêtre spécifiée.
 * 
 * @param window La fenêtre SFML sur laquelle dessiner l'écran de fin de jeu multijoueur.
 */
void GameOverMultiScreen::draw(sf::RenderWindow &window) {
    window.draw(gameOverText);
    window.draw(gagnantText);
    window.draw(retryText);
    window.draw(quitText);
}


