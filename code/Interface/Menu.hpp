#ifndef MENU_HPP
#define MENU_HPP
                                            /// Bibliothèques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../global_variables.hpp"
#include <tuple>

                                            /// Code Principal ///
class Menu {
public:
    Menu(sf::RenderWindow& window, sf::Music& music) : window(window), music(music) {}

    std::tuple <std::string, float> run();

private:
    sf::RenderWindow& window;
    sf::Music& music;
    float volume = VolumeGeneral; // Volume sonore initial
};

#endif // MENU_HPP