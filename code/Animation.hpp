#ifndef ANIMATION_HPP
#define ANIMATION_HPP
                                            // Bibliothéques //
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

                                            // Code Principal //
/**
 * @brief Gère l'animation d'un sprite à l'aide d'une série d'images (spritesheet).
 * 
 * 
 * @param t Le paramètre "t" est une référence à un objet sf::Texture. C'est la texture qui sera
 * utilisée pour les images d'animation.
 * @param x Le paramètre "x" dans le constructeur Animation représente la coordonnée x de la position
 * de départ des images d'animation sur la texture.
 * @param y Le paramètre "y" dans le constructeur Animation représente la coordonnée y du coin
 * supérieur gauche de la première image de l'animation dans la texture.
 * @param w Le paramètre "w" dans le constructeur Animation représente la largeur de chaque image de
 * l'animation.
 * @param h Le paramètre "h" dans le constructeur Animation représente la hauteur de chaque image de
 * l'animation. Il est utilisé pour définir la taille des images dans les objets sf::IntRect qui sont
 * stockés dans le vecteur frames.
 * @param count Le paramètre "count" dans le constructeur Animation représente le nombre d'images dans
 * l'animation. Il détermine combien d'images seront ajoutées au vecteur "frames". Chaque cadre est un
 * rectangle défini par sa position (x, y) et sa largeur et hauteur (w, h).
 * @param Speed Le paramètre "Vitesse" du constructeur Animation est utilisé pour contrôler la vitesse
 * à laquelle les images d'animation sont lues. Il détermine la rapidité avec laquelle l'animation
 * progresse d'une image à la suivante. Une valeur plus élevée pour Vitesse accélérera la lecture de
 * l'animation, tandis qu'une valeur inférieure la rendra plus lente.
 */
class Animation
{
   public:
   float Frame, speed;
   sf::Sprite sprite;
   std::vector<sf::IntRect> frames;
   /**
    * @brief Constructeur par défaut
    * 
    */
   Animation(){}

   /**
    * @brief Constructeur avec paramètres permettant d'initialisées les attributs.
    * 
    */
   Animation (sf::Texture &t, int x, int y, int w, int h, int count, float Speed);


   void update();

   bool isEnd();

};

#endif // ANIMATION_HPP