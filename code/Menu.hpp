#ifndef MENU_HPP
#define MENU_HPP
                                            /// Bibliothèques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

                                            /// Code Principal ///
class Menu {
public:
    enum class ActionMenu {Quitter,Jouer};

    Menu(sf::RenderWindow& window, sf::Music& music) : window(window), music(music) {}

    ActionMenu run();

private:
    sf::RenderWindow& window;
    sf::Music& music;
    float volume = 0.5f; // Volume sonore initial
};

#endif // MENU_HPP