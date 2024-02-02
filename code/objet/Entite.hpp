#ifndef ENTITE_HPP
#define ENTITE_HPP
                                            /// Bibliothéques ///
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../Animation.hpp"

                                            /// Code Principal ///

class Entite
{
    public:

    float x,y,vx,vy,R,angle;
    bool life;
    std::string name;
    Animation anim;

    Entite(){life=1;}

    void settings(Animation &a,int X,int Y,float Angle=0,int radius=1);

    virtual void update();

    void draw(sf::RenderWindow &app);

    virtual ~Entite();
};

#endif // ENTITE_HPP