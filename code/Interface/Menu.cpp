                                            // Bibliothèques //
#include "Menu.hpp"  
#include "../global_variables.hpp"       
#include <tuple>                         

                                            // Variables //

                                            // Code Principal //

/**
 * La fonction run dans la classe Menu affiche un écran de menu avec des boutons et gère les
 * interactions de l'utilisateur telles que cliquer sur des boutons et faire glisser un indicateur de
 * volume.
 * 
 * @return La fonction `run()` renvoie un tuple contenant une chaîne et un float. La chaîne représente
 * l'action sélectionnée par l'utilisateur (par exemple, "JouerSolo", "JouerMulti", "Quitter"), et le
 * float représente le niveau de volume sélectionné par l'utilisateur.
 */
std::tuple <std::string, float> Menu::run() {
    sf::Font font;
    if (!font.loadFromFile("Ressources/police/arial/arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return std::make_tuple("Quitter", 0);
    }

    sf::Text title("Asteroid Game", font, 50);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(200, 100);

    sf::Text BoutonSolo("Solo", font, 30);
    BoutonSolo.setFillColor(sf::Color::White);
    BoutonSolo.setPosition(300, 250);

    sf::Text BoutonMultijoueur("Multijoueur Local", font, 30);
    BoutonMultijoueur.setFillColor(sf::Color::White);
    BoutonMultijoueur.setPosition(300, 300);

    sf::Text BoutonQuitter("Quitter", font, 30);
    BoutonQuitter.setFillColor(sf::Color::White);
    BoutonQuitter.setPosition(300, 400);

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

    // Test pour le pictogramme de son
    sf::Texture SonTexture;
    if (!SonTexture.loadFromFile("Ressources/image/Pictogramme_son.png")) {
        std::cerr << "Failed to load logo image." << std::endl;
        // Gérer l'échec du chargement de l'image
    }
    sf::Sprite PictogrammeSonSprite(SonTexture);
    PictogrammeSonSprite.setPosition(window.getSize().x - 290, window.getSize().y - 55);
    float scaleFactor = 0.1f;
    PictogrammeSonSprite.setScale(scaleFactor, scaleFactor);

    // Test pour le fond d'écran
    sf::Texture tbackground;
    tbackground.loadFromFile("Ressources/image/Menu_Background.png");
    tbackground.setSmooth(true);
    sf::Sprite background(tbackground);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (BoutonSolo.getGlobalBounds().contains(mousePos)) {
                    // Action lorsque le bouton "Solo" est cliqué
                    std::cout << "Bouton Solo cliqué" << std::endl;
                    clickSound.play(); // Jouer le son de clic
                    window.close(); // Fermer la fenêtre lorsque le bouton "Jouer" est cliqué
                    return std::make_tuple("JouerSolo", volume);
                }
                else if (BoutonMultijoueur.getGlobalBounds().contains(mousePos)) {
                    // Action lorsque le bouton "Multijoueur" est cliqué
                    std::cout << "Bouton Multijoueur Local cliqué" << std::endl;
                    clickSound.play(); // Jouer le son de clic
                    window.close(); // Fermer la fenêtre lorsque le bouton "Jouer" est cliqué
                    return std::make_tuple("JouerMulti", volume);
                }
                else if (BoutonQuitter.getGlobalBounds().contains(mousePos)) {
                    // Action lorsque le bouton "Quitter" est cliqué
                    std::cout << "Bouton quitter cliqué!" << std::endl;
                    clickSound.play(); // Jouer le son de clic
                    window.close(); // Fermer la fenêtre lorsque le bouton "Quitter" est cliqué
                    return std::make_tuple("Quitter", volume);
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
                if (BoutonSolo.getGlobalBounds().contains(mousePos)) {BoutonSolo.setFillColor(hoverColor);} 
                else {BoutonSolo.setFillColor(normalColor);}
                if (BoutonMultijoueur.getGlobalBounds().contains(mousePos)) {BoutonMultijoueur.setFillColor(hoverColor);} 
                else {BoutonMultijoueur.setFillColor(normalColor);}
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
        window.draw(background);
        window.draw(title);
        window.draw(BoutonSolo);
        window.draw(BoutonMultijoueur);
        window.draw(BoutonQuitter);
        window.draw(PictogrammeSonSprite);
        window.draw(volumeBar);
        window.draw(volumeIndicator);
        window.display();
    }

return std::make_tuple("Quitter", volume);
}
