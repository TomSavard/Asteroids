                                            // Bibliothèques //
#include "Entite.hpp"
#include "../Animation.hpp"
#include "../global_variables.hpp"                            

                                            // Code Principal //

/**
 * La fonction « settings » définit l'animation, la position, l'angle et le rayon d'une entité.
 * 
 * @param a Le paramètre "a" est de type Animation et permet de définir l'animation de l'entité.
 * @param X Le paramètre X représente la coordonnée x de la position de l'entité.
 * @param Y Le paramètre Y représente la position verticale de l'entité sur l'écran.
 * @param Angle Le paramètre angle représente l'angle de rotation de l'entité. Il permet de préciser
 * l'angle de rotation initial de l'entité lors de sa création.
 * @param radius Le paramètre radius représente le rayon de l'entité. Il est utilisé pour déterminer la
 * taille de la hitbox ou de la zone de détection de collision de l'entité.
 */
void Entite::settings(Animation &a,int X,int Y,float Angle,int radius)
{
    anim = a;
    x=X; y=Y;
    angle = Angle;
    R = radius;
}

/**
 * @brief Dessine une entité sur une fenêtre SFML avec une position et une rotation spécifiques.
 * 
 * @param app Le paramètre "app" est une référence à l'objet sf::RenderWindow qui représente la fenêtre
 * de l'application. Il est utilisé pour dessiner le sprite sur la fenêtre.
 */
void Entite::draw(sf::RenderWindow &app)
{
    anim.sprite.setPosition(x,y);
    anim.sprite.setRotation(angle+90);
    app.draw(anim.sprite);
}


/**
 * @brief Le destructeur de la classe Entite.
 * 
 * Ce destructeur est virtuel car il dépend de la structure des classes dérivées.
 */
Entite::~Entite() {
}


/** 
 * @brief fonction d'espace réservé qui est destinée à être
* remplacée par les classes dérivées.
* Elle est utilisée pour mettre à jour l'état de l'entité, comme sa
* position, sa vitesse ou toute autre propriété susceptible de changer au fil du temps. La mise en
* œuvre de cette fonction variera en fonction du comportement spécifique de l'entité.
*/
void Entite::update(){
};


/**
 * @brief renvoie l'équipe d'une entité.
 * 
 * @return la valeur de la variable "équipe".
 */
int Entite::getTeam()
{
    return team;
}
/**
 * @brief définit l'équipe d'une entité à la valeur spécifiée.
 * 
 * @param choixTeam Le paramètre « choixTeam » est un entier qui représente le numéro d'équipe ou
 * identifiant de l'entité.
 */
void Entite::setTeam(int choixTeam)
{
    team = choixTeam;
}


/**
 * @brief renvoie la valeur de la variable "life".
 * 
 * @return la valeur de la variable "vie".
 */
bool Entite::getLife()
{
    return life;
}
/**
 * @brief fixe la valeur de la variable "life" à la valeur passée en paramètre.
 * 
 * @param newlife La nouvelle valeur de la variable "life". C'est une valeur booléenne indiquant si
 * l'entité est vivante ou non.
 */
void Entite::setLife(bool newlife)
{
    life = newlife;
}


/**
 * @brief renvoie le nom d'une entité.
 * 
 * @return une chaîne, qui est la valeur de la variable "name".
 */
std::string Entite::getName()
{
    return name;
}
/**
 * @brief définit le nom d'une entité sur une nouvelle valeur.
 * 
 * @param newName Le nouveau nom qui sera attribué à la variable "name".
 */
void Entite::setName(std::string newName)
{
    name = newName;
}


/**
 * @brief renvoie un pointeur sur l'objet "anim" de la classe "Entite".
 * 
 * @return un pointeur vers un objet de type Animation.
 */
Animation* Entite::getAnim()
{
    return &anim;
}
/**
 * @brief définit l'animation d'une entité sur une nouvelle animation.
 * 
 * @param newAnim La nouvelle animation que vous souhaitez définir pour l'entité.
 */
void Entite::setAnim(Animation newAnim)
{
    anim = newAnim;
}


/**
 * @brief renvoie la valeur de la variable "x" sous forme de flottant.
 * 
 * @return la valeur de la variable "x".
 */
float Entite::getx()
{
    return x;
}
/**
 * @brief définit la valeur de la variable x à une nouvelle valeur.
 * 
 * @param newX Le paramètre "newX" est une variable de type float qui représente la nouvelle valeur de
 * la coordonnée x de l'entité.
 */
void Entite::setx(float newX)
{
    x = newX;
}

/**
 * @brief renvoie la valeur de la variable "y" sous forme de flottant.
 * 
 * @return La valeur y de l'objet Entite.
 */
float Entite::gety()
{
    return y;
}
/**
 * @brief définit la valeur de la variable "y" à une nouvelle valeur.
 * 
 * @param newY Le paramètre "newY" est une valeur flottante qui représente la nouvelle coordonnée y de
 * l'entité.
 */
void Entite::sety(float newY)
{
    y = newY;
}

/**
 * @brief renvoie la valeur de la variable "vx" sous forme de float.
 * 
 * @return la valeur de la variable "vx".
 */
float Entite::getvx()
{
    return vx;
}
/**
 * @brief définit la valeur de la variable "vx" à une nouvelle valeur.
 * 
 * @param newVX La nouvelle valeur de la vitesse x de l'entité.
 */
void Entite::setvx(float newVX)
{
    vx = newVX;
}

/**
 * @brief renvoie la valeur de la variable "vy" sous forme de float.
 * 
 * @return la valeur de la variable "vy".
 */
float Entite::getvy()
{
    return vy;
}
/**
 * @brief définit la valeur de la variable vy dans la classe Entite.
 * 
 * @param newVY Le paramètre newVY est un flottant qui représente la nouvelle valeur de la variable vy
 * (vitesse verticale) de l'objet Entite.
 */
void Entite::setvy(float newVY)
{
    vy = newVY;
}

/**
 * @brief renvoie la valeur de la variable "R" sous forme de float.
 * 
 * @return la valeur de la variable "R".
 */
float Entite::getR()
{
    return R;
}
/**
 * @brief définit la valeur de la variable R dans la classe Entite.
 * 
 * @param newR Le paramètre newR est un flottant qui représente la nouvelle valeur de la variable R
 * Rayon de la hitbox de l'objet Entite.
 */
void Entite::setR(float newR)
{
    R = newR;
}

/**
 * @brief renvoie la valeur de la variable "angle" sous forme de float.
 * 
 * @return la valeur de la variable "angle".
 */
float Entite::getangle()
{
    return angle;
}
/**
 * @brief définit la valeur de la variable angle dans la classe Entite.
 * 
 * @param newAngle Le paramètre newAngle est un flottant qui représente la nouvelle valeur de la variable angle.
 */
void Entite::setangle(float newAngle)
{
    angle = newAngle;
}