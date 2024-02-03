/* Ce fichier contient l'ensemble des constantes du jeu. Cela permet une centralisation des données,
supprime la redondance et facilite les modifications*/
#include "global_variables.hpp"

sf::Color normalColor = sf::Color::White;
sf::Color hoverColor = sf::Color(200, 200, 200);

const int LargeurFenetre = 1200;
const int HauteurFenetre = 800;

float DEGTORAD = 0.0174533f;
float VolumeGeneral = 1.f;

int NombreAsteroideStart = 15;
int NombreResidu = 4;