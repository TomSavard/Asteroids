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

//     sf::CircleShape circle(R);
//     circle.setFillColor(sf::Color(255,0,0,170));
//     circle.setPosition(x,y);
//     circle.setOrigin(R,R);
//     app.draw(circle);
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


bool Entite::getLife()
{
    return life;
}
void Entite::setLife(bool newlife)
{
    life = newlife;
}


std::string Entite::getName()
{
    return name;
}
void Entite::setName(std::string newName)
{
    name = newName;
}


Animation* Entite::getAnim()
{
    return &anim;
}
void Entite::setAnim(Animation newAnim)
{
    anim = newAnim;
}


float Entite::getx()
{
    return x;
}
void Entite::setx(float newX)
{
    x = newX;
}

float Entite::gety()
{
    return y;
}
void Entite::sety(float newY)
{
    y = newY;
}

float Entite::getvx()
{
    return vx;
}
void Entite::setvx(float newVX)
{
    vx = newVX;
}

float Entite::getvy()
{
    return vy;
}
void Entite::setvy(float newVY)
{
    vy = newVY;
}

float Entite::getR()
{
    return R;
}
void Entite::setR(float newR)
{
    R = newR;
}

float Entite::getangle()
{
    return angle;
}
void Entite::setangle(float newAngle)
{
    angle = newAngle;
}