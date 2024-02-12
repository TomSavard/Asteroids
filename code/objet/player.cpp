                                            /// Bibliothèques ///
#include "player.hpp"
#include "Entite.hpp"
#include "../Animation.hpp"
#include "../global_variables.hpp"                            

                                            /// Code Principal ///

void player::update()
{
    if (thrust)
    {
        this->setvx(this->getvx() + cos(this->getangle()*DEGTORAD)*0.2);
        this->setvy(this->getvy() + sin(this->getangle()*DEGTORAD)*0.2);
    }
    else
    {
        this->setvx(this->getvx() * 0.99);
        this->setvy(this->getvy() * 0.99);
    }

    int maxSpeed=15;
    float speed = sqrt(this->getvx()*this->getvx()+this->getvy()*this->getvy());
    if (speed>maxSpeed)
    {
        this->setvx(this->getvx() * maxSpeed/speed);
        this->setvy(this->getvy() * maxSpeed/speed);
    }

    this->setx(this->getx() + this->getvx());
    this->sety(this->gety() + this->getvy());

    if (this->getx()>LargeurFenetre) this->setx(0); if (this->getx()<0) this->setx(LargeurFenetre);
    if (this->gety()>HauteurFenetre) this->sety(0); if (this->gety()<0) this->sety(HauteurFenetre);
}

void player::draw_bouclier (sf::RenderWindow &app, bool invincible)
{
    if (invincible){
        sf::CircleShape circle(this->getR());
        circle.setFillColor(sf::Color(255,0,0,170));
        circle.setPosition(this->getx(),this->gety());
        circle.setOrigin(this->getR(),this->getR());
        app.draw(circle);
    }
}