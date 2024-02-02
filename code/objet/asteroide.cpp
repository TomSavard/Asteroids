                                            /// Bibliothèques ///
#include "asteroide.hpp"
#include "Entite.hpp"
#include "../Animation.hpp"
#include "../global_variables.hpp"                            

                                            /// Code Principal ///

void asteroide::update()
{
    x+=vx;
    y+=vy;

    if (x>LargeurFenetre) x=0;  if (x<0) x=LargeurFenetre;
    if (y>HauteurFenetre) y=0;  if (y<0) y=HauteurFenetre;
}

