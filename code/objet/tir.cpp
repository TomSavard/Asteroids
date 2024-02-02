                                            /// Bibliothèques ///
#include "tir.hpp"
#include "Entite.hpp"
#include "../Animation.hpp"
#include "../global_variables.hpp"                            

                                            /// Code Principal ///

void  tir::update()
{
    vx=cos(angle*DEGTORAD)*6;
    vy=sin(angle*DEGTORAD)*6;
    // angle+=rand()%7-3;  /*try this*/
    x+=vx;
    y+=vy;

    if (x>LargeurFenetre || x<0 || y>HauteurFenetre || y<0) life=0;
}


