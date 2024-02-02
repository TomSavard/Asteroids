#ifndef ANIMATION_HPP
#define ANIMATION_HPP
                                            /// Bibliothéques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

                                            /// Code Principal ///


class Animation
{
   public:
   float Frame, speed;
   sf::Sprite sprite;
   std::vector<sf::IntRect> frames;

   Animation(){}

   Animation (sf::Texture &t, int x, int y, int w, int h, int count, float Speed);


   void update();

   bool isEnd();

};


#endif // ANIMATION_HPP