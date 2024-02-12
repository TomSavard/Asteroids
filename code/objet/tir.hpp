#ifndef TIR_HPP
#define TIR_HPP
                                            /// Bibliothéques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../Animation.hpp"
#include "Entite.hpp"

                                            /// Code Principal ///

class tir: public Entite
{

  public:
  tir()
  {
    name="tir";
  }


  void  update();

};

#endif // TIR_HPP