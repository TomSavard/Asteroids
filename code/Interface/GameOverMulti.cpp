/**
 * Le code ci-dessous définit une classe appelée GameOverMultiScreen qui affiche un écran de jeu pour un
 * jeu multijoueur, montrant le gagnant et offrant des options pour redémarrer ou quitter le jeu.
 * 
 * @param gagnant Le paramètre « gagnant » représente le gagnant de la partie dans un scénario
 * multijoueur. Il s'agit d'une valeur entière qui peut être 1 ou 2, indiquant le numéro du joueur ou
 * de l'équipe qui a gagné la partie.
 */
                                            /// Bibliothèques ///
#include "GameOverMulti.hpp"     
#include "../global_variables.hpp"                             

                                            /// Code Principal ///

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

void GameOverMultiScreen::draw(sf::RenderWindow &window) {
    window.draw(gameOverText);
    window.draw(gagnantText);
    window.draw(retryText);
    window.draw(quitText);
}


