                                            /// Bibliothèques ///
#include "Menu.hpp"  
#include "../global_variables.hpp"                                

                                            /// Code Principal ///

Menu::ActionMenu Menu::run() {
    sf::Font font;
    if (!font.loadFromFile("Ressources/police/arial/arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return ActionMenu::Quitter;
    }

    sf::Text title("Asteroid Game", font, 50);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(200, 100);

    sf::Text BoutonJouer("Jouer", font, 30);
    BoutonJouer.setFillColor(sf::Color::White);
    BoutonJouer.setPosition(300, 250);

    sf::Text BoutonQuitter("Quitter", font, 30);
    BoutonQuitter.setFillColor(sf::Color::White);
    BoutonQuitter.setPosition(300, 350);

    sf::RectangleShape volumeBar(sf::Vector2f(200, 20));
    volumeBar.setFillColor(sf::Color(200, 200, 200)); // Couleur gris clair
    volumeBar.setPosition(window.getSize().x - 250, window.getSize().y - 50);

    sf::CircleShape volumeIndicator(10);
    volumeIndicator.setFillColor(sf::Color::White);
    volumeIndicator.setOutlineColor(sf::Color::Black);
    volumeIndicator.setOutlineThickness(2);
    volumeIndicator.setOrigin(5, 5);
    volumeIndicator.setPosition(window.getSize().x - 250 + volume * 200, window.getSize().y - 45);

    bool isDragging = false;

    // Charger le son pour le clic sur le bouton
    sf::SoundBuffer clickSoundBuffer;
    if (!clickSoundBuffer.loadFromFile("Ressources/audio/Bouton2.wav")) {std::cerr << "Failed to load click sound file" << std::endl;}
    sf::Sound clickSound;
    clickSound.setBuffer(clickSoundBuffer);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (BoutonJouer.getGlobalBounds().contains(mousePos)) {
                    // Action lorsque le bouton "Jouer" est cliqué
                    std::cout << "Bouton Jouer cliqué" << std::endl;
                    clickSound.play(); // Jouer le son de clic
                    window.close(); // Fermer la fenêtre lorsque le bouton "Jouer" est cliqué
                    return ActionMenu::Jouer;
                }
                else if (BoutonQuitter.getGlobalBounds().contains(mousePos)) {
                    // Action lorsque le bouton "Quitter" est cliqué
                    std::cout << "Bouton quitter cliqué!" << std::endl;
                    clickSound.play(); // Jouer le son de clic
                    window.close(); // Fermer la fenêtre lorsque le bouton "Quitter" est cliqué
                    return ActionMenu::Quitter;
                }
                else if (volumeIndicator.getGlobalBounds().contains(mousePos)) {
                    isDragging = true;
                }
            } 
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isDragging = false;
            } 
            else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                // Gestion du survol des boutons
                if (BoutonJouer.getGlobalBounds().contains(mousePos)) {BoutonJouer.setFillColor(hoverColor);} 
                else {BoutonJouer.setFillColor(normalColor);}
                if (BoutonQuitter.getGlobalBounds().contains(mousePos)) {BoutonQuitter.setFillColor(hoverColor);}
                else {BoutonQuitter.setFillColor(normalColor);}
                // Déplacement du bouton de volume si l'utilisateur est en train de le glisser
                if (isDragging) {
                    float newVolume = (mousePos.x - (window.getSize().x - 250)) / 200.0f;
                    if (newVolume < 0)
                        newVolume = 0;
                    else if (newVolume > 1)
                        newVolume = 1;
                    volume = newVolume;
                    music.setVolume(volume * 100); // Réglez le volume sur une échelle de 0 à 100
                    volumeIndicator.setPosition(window.getSize().x - 250 + volume * 200, window.getSize().y - 45);
                }
            }
        }
        window.clear();
        window.draw(title);
        window.draw(BoutonJouer);
        window.draw(BoutonQuitter);
        window.draw(volumeBar);
        window.draw(volumeIndicator);
        window.display();
    }
return ActionMenu::Quitter;
}
