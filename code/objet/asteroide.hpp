#ifndef ASTEROIDE_HPP
#define ASTEROIDE_HPP
                                            // Bibliothéques //
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../Animation.hpp"
#include "Entite.hpp"

                                            // Code Principal //
/**
 * @brief Cette objet regroupe l'ensemble des astres qui volent à l'écran. Ces derniers peuvent être d'apparences, de taille ou encore de vitesse diférentes. 
 * 
 */
class asteroide: public Entite
{
   public:
   /**
   * @brief Constructeur par défaut.
   * 
   * Le constructeur par défaut de la classe Entite. On initialise aléatoirement les vitesses vx et vy.
   */
   asteroide()
   {
     this->setvx(rand()%8-4);
     this->setvy(rand()%8-4);
     this->setName("asteroide");
   }
  /**
   * @brief Methode permettant la mise à jour de la position de l'astéroïde.
   * 
   */
   void update();
};

#endif // ASTEROIDE_HPP