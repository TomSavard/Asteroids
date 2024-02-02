#ifndef ASTEROIDE_HPP
#define ASTEROIDE_HPP
                                            /// Bibliothéques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../Animation.hpp"
#include "Entite.hpp"

                                            /// Code Principal ///

class asteroide: public Entite
{
   public:
   asteroide()
   {
     vx=rand()%8-4;
     vy=rand()%8-4;
     name="asteroide";
   }

   void update();
};

#endif // ASTEROIDE_HPP