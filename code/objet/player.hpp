#ifndef PLAYER_HPP
#define PLAYER_HPP
                                            /// Bibliothéques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../Animation.hpp"
#include "Entite.hpp"

                                            /// Code Principal ///

class player: public Entite
{

public:
  bool thrust;

  player() 
  {
    name="player";
  }

  void update();

  void draw_bouclier(sf::RenderWindow &app , bool invincible);

};

#endif // PLAYER_HPP