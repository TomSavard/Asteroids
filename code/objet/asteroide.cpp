                                            /// Bibliothèques ///
#include "asteroide.hpp"
#include "Entite.hpp"
#include "../Animation.hpp"
#include "../global_variables.hpp"                            

                                            /// Code Principal ///

void asteroide::update()
{
    this->setx(this->getx() + this->getvx());
    this->sety(this->gety() + this->getvy());

    if (this->getx()>LargeurFenetre) this->setx(0);  if (this->getx()<0) this->setx(LargeurFenetre);
    if (this->gety()>HauteurFenetre) this->sety(0);  if (this->gety()<0) this->sety(HauteurFenetre);
}

