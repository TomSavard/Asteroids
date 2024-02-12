                                            /// Bibliothèques ///
#include "tir.hpp"
#include "Entite.hpp"
#include "../Animation.hpp"
#include "../global_variables.hpp"                            

                                            /// Code Principal ///

void  tir::update()
{
    this->setvx(cos(this->getangle()*DEGTORAD)*6);
    this->setvy(sin(this->getangle()*DEGTORAD)*6);
    // angle+=rand()%7-3;  /*try this*/
    this->setx(this->getx() + this->getvx());
    this->sety(this->gety() + this->getvy());

    if (this->getx()>LargeurFenetre || this->getx()<0 || this->gety()>HauteurFenetre || this->gety()<0) this->setLife(false);
}

