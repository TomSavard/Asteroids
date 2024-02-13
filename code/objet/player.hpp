#ifndef PLAYER_HPP
#define PLAYER_HPP
                                            // Bibliothéques //
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../Animation.hpp"
#include "Entite.hpp"

                                            // Code Principal //
/**
 * @brief Classe player correspondant au vaisseau du joueur. Il peut se déplacer et tirer avec son blaster.
 * 
 */
class player: public Entite
{

public:
  bool thrust; // à mettre en privée

  player() 
  {
    this->setName("player");
  }

  void update();

  /**
   * @brief permet une invincibilité temporaire au lancement.
   * 
   * @param app pointeur sf::RenderWindow qui permet l'affichage
   * @param invincible bool true = invincible, false = vulnérable
   */
  void draw_bouclier(sf::RenderWindow &app , bool invincible);

};

#endif // PLAYER_HPP