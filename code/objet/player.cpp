                                            /// Bibliothèques ///
#include "player.hpp"
#include "Entite.hpp"
#include "../Animation.hpp"
#include "../global_variables.hpp"                            

                                            /// Code Principal ///

void player::update()
{
    if (thrust)
    { vx+=cos(angle*DEGTORAD)*0.2;
    vy+=sin(angle*DEGTORAD)*0.2; }
    else
    { vx*=0.99;
    vy*=0.99; }

int maxSpeed=15;
float speed = sqrt(vx*vx+vy*vy);
if (speed>maxSpeed)
    { vx *= maxSpeed/speed;
    vy *= maxSpeed/speed; }

x+=vx;
y+=vy;

if (x>LargeurFenetre) x=0; if (x<0) x=LargeurFenetre;
if (y>HauteurFenetre) y=0; if (y<0) y=HauteurFenetre;
}


