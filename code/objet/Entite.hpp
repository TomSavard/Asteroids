#ifndef ENTITE_HPP
#define ENTITE_HPP
                                            // Bibliothéques //
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../Animation.hpp"

                                            // Code Principal //
/**
 * @brief Classe la plus générique regroupant les propriétés des différents objets.
 * 
 * Cette classe possède de nombreux paramètres tous passés en privée afin de garantir une certaine sécuritée.
 * @param team int correspondant au numéro de l'équipe
 * @param life bool indiquant si l'entité est détruite ou non.
 * @param name string permettant la discrimination des entitées.
 * @param anim Animation donnant accès à un sprite.
 * @param x float position horizontale
 * @param y float position verticale
 * @param vx float vitesse horizontale
 * @param vy float vitesse verticale
 * @param R float rayon de la hitbox
 * @param angle float orientation de l'entité dans le plan 
 * 
 * 
 */
class Entite
{
    private :
    int team;
    bool life;
    std::string name;
    Animation anim;
    float x,y,vx,vy,R,angle;

    public:

    /**
     * Le constructeur par défaut de la classe Entite. On initialise l'entité comme étant vivante (life=1;).
     */
    Entite(){life=1;}

    /**
     * @brief permet le paramétrage de l'entité en définissant la valeur de ses attributs.
     * 
     * @param a animation associée à l'objet
     * @param X position horizontale de l'entité
     * @param Y position verticale
     * @param Angle orientation dans le plan de l'objet
     * @param radius rayon de la hitbox
     */
    void settings(Animation &a,int X,int Y,float Angle=0,int radius=1);

    virtual void update();

    void draw(sf::RenderWindow &app);


    float getx();
    void setx(float newX);

    float gety();
    void sety(float newY);

    float getvx();
    void setvx(float newVX);

    float getvy();
    void setvy(float newVY);

    float getR();
    void setR(float newR);

    float getangle();
    void setangle(float newAngle);


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