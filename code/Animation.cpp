                                            // Bibliothèques //
#include "Animation.hpp"
#include "global_variables.hpp"                            

                                            // Code Principal //
/**
 * 
 * Initialise une animation avec une texture, une position de départ, des dimensions de trame,
 * un nombre de trames, et une vitesse spécifiée.
 * 
 * @param t La texture à utiliser pour l'animation.
 * @param x La position horizontale de départ de la première trame.
 * @param y La position verticale de départ de la première trame.
 * @param w La largeur de chaque trame.
 * @param h La hauteur de chaque trame.
 * @param count Le nombre total de trames dans l'animation.
 * @param Speed La vitesse de l'animation.
 * 
 * @note Ce constructeur suppose que la texture est correctement chargée et que les dimensions
 * de la trame et le nombre de trames sont valides.
 */
Animation::Animation (sf::Texture &t, int x, int y, int w, int h, int count, float Speed)
{
  Frame = 0;
  speed = Speed;

  for (int i=0;i<count;i++)
  frames.push_back( sf::IntRect(x+i*w, y, w, h)  );

  sprite.setTexture(t);
  sprite.setOrigin(w/2,h/2);
  sprite.setTextureRect(frames[0]);
}

/**
 * @brief Met à jour l'animation.
 * 
 * Cette méthode met à jour l'animation en incrémentant le compteur de trame en fonction de la vitesse
 * de l'animation. Elle assure également que le compteur de trame boucle pour éviter de sortir
 * des limites du vecteur de trames.
 * 
 * @note Cette méthode suppose que le sprite et le vecteur de trames sont correctement initialisés.
 */
void Animation::update()
{
  Frame += speed;
  int n = frames.size();
  if (Frame >= n) Frame -= n;
  if (n>0) sprite.setTextureRect( frames[int(Frame)] );
}

/**
 * @brief Vérifie si l'animation est terminée.
 * 
 * Cette méthode vérifie si l'animation est terminée en comparant la position actuelle de la trame
 * avec la taille du vecteur de trames, ajustée en fonction de la vitesse de l'animation.
 * 
 * @return true si l'animation est terminée, false sinon.
 * 
 * @note Cette méthode suppose que le vecteur de trames et la vitesse de l'animation sont correctement définis.
 */
bool Animation::isEnd()
{
  return Frame+speed>=frames.size();
}
