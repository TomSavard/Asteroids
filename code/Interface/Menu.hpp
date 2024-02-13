#ifndef MENU_HPP
#define MENU_HPP
                                            // Bibliothèques //
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../global_variables.hpp"
#include <tuple>

                                            // Code Principal //
/**
 * @brief Classe représentant le menu d'accueil du jeu.
 * 
 * Cette classe gère l'affichage et l'interaction avec le menu du jeu permettant de sélectionner le mode de jeu ou encore le volume sonore.
 */
class Menu {
public:
    /**
     * @brief Constructeur du Menu. Il fait appel à deux arguments afin de pouvoir effectuer l'affichage et avoir une musique de fond.
     * 
     * @param window pointeur sf::RenderWindow qui permet l'affichage des éléments.
     * @param music pointeur sf::Music qui donne accès à la musique chargée.
     */
    Menu(sf::RenderWindow& window, sf::Music& music) : window(window), music(music) {}

    std::tuple <std::string, float> run();

private:
    sf::RenderWindow& window;
    sf::Music& music;
    float volume = VolumeGeneral; // Volume sonore initial
};

#endif // MENU_HPP