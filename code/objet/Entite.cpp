                                            /// Bibliothèques ///
#include "Entite.hpp"
#include "../Animation.hpp"
#include "../global_variables.hpp"                            

                                            /// Code Principal ///

void Entite::settings(Animation &a,int X,int Y,float Angle,int radius)
{
    anim = a;
    x=X; y=Y;
    angle = Angle;
    R = radius;
}

void Entite::draw(sf::RenderWindow &app)
{
    anim.sprite.setPosition(x,y);
    anim.sprite.setRotation(angle+90);
    app.draw(anim.sprite);

    sf::CircleShape circle(R);
    circle.setFillColor(sf::Color(255,0,0,170));
    circle.setPosition(x,y);
    circle.setOrigin(R,R);
//  app.draw(circle);
}

Entite::~Entite() {
    // Destructeur car terminal se plaint
}

void Entite::update(){
    // besoin de la def sinon le terminal n'est pas content
};

int Entite::getTeam()
{
    return team;
}

void Entite::setTeam(int choixTeam)
{
    team = choixTeam;
}