#ifndef VIE_HPP_INCLUDED
#define VIE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "vaisseau.hpp"

using namespace sf;

typedef struct
{
    Vector2f taille;
    RectangleShape barre;
    int hpBase;
}Vie;

Vie addBarreDeVie(Vector2f taille, int hp);
void changeBarreVie(Vaisseau *vaisseau, Vie *vie);
#endif // VIE_HPP_INCLUDED
