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
    private :
    int team;
    bool life;
    std::string name;
    Animation anim;
    public:

    float x,y,vx,vy,R,angle;

    Entite(){life=1;}

    void settings(Animation &a,int X,int Y,float Angle=0,int radius=1);

    virtual void update();

    void draw(sf::RenderWindow &app);

    int getTeam();
    void setTeam(int choixTeam);

    bool getLife();
    void setLife(bool newlife);

    std::string getName();
    void setName(std::string newName);

    Animation* getAnim(); // passage par pointeur sinon la modification via update n'est pas prise en compte.
    void setAnim(Animation newAnim);

    virtual ~Entite();

};

#endif // ENTITE_HPP