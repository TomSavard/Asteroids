                                            /// Bibliothèques ///
#include "GameOver.hpp"     
#include "../global_variables.hpp"                             

                                            /// Code Principal ///

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

void GameOverScreen::draw(sf::RenderWindow &window) {
    window.draw(gameOverText);
    window.draw(scoreText);
    window.draw(retryText);
    window.draw(quitText);
}


