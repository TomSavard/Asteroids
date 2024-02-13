#ifndef TIR_HPP
#define TIR_HPP
                                            // Bibliothéques //
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../Animation.hpp"
#include "Entite.hpp"

                                            // Code Principal //
/**
 * @brief Ce sont les projectiles du blaster. Ils peuvent entrer en collision avec les entités ennemies (astéroides ou autre vaisseau).
 * 
 */
class tir: public Entite
{

  public:
  /**
   * @brief Constructeur par défaut de la classe tir.
   * 
   */
  tir()
  {
    this->setName("tir");
  }


  void  update();

};

#endif // TIR_HPP