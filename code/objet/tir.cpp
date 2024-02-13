                                            // Bibliothèques //
#include "tir.hpp"
#include "Entite.hpp"
#include "../Animation.hpp"
#include "../global_variables.hpp"                            

                                            // Code Principal //
/**
 * @brief Mise en oeuvre spécifique à la classe tir de la fonction générique update 
 * 
 * Les tirs ont une trajectoire rectiligne uniforme. Ils sont détruits une fois sortis de l'écran.
 */
void  tir::update()
{
    this->setvx(cos(this->getangle()*DEGTORAD)*6);
    this->setvy(sin(this->getangle()*DEGTORAD)*6);
    // angle+=rand()%7-3;  /*try this*/
    this->setx(this->getx() + this->getvx());
    this->sety(this->gety() + this->getvy());

    if (this->getx()>LargeurFenetre || this->getx()<0 || this->gety()>HauteurFenetre || this->gety()<0) this->setLife(false);
}

