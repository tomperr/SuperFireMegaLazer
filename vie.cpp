#include "vie.hpp"
#include "draw.hpp"
#include "vaisseau.hpp"



Vie addBarreDeVie(Vector2f taille, int hp)
{
    // Creer une barre de vie
    Vie vie;
    vie.taille.x = taille.x;
    vie.taille.y=taille.y;
    vie.hpBase=hp;
    vie.barre.setSize(taille);
    vie.barre.setFillColor(Color::Green);
    vie.barre.setOrigin(0,0);
    return vie;
}

void changeBarreVie(Vaisseau *vaisseau, Vie *vie)
{
    // Calcul la taille et la couleur de la barre de vie
    vie->taille.x = 100*((float)vaisseau->hp/(float)vie->hpBase);
    vie->barre= RectangleShape(vie->taille);
    vie->barre.setOrigin(0,0);
    if(vie->taille.x>75)
        vie->barre.setFillColor(sf::Color(0,255,0));
    else if(vie->taille.x>50&& vie->taille.x<=75)
        vie->barre.setFillColor(sf::Color(100,255,0));
    else if(vie->taille.x>25 && vie->taille.x<=50)
        vie->barre.setFillColor(sf::Color(200,255,0));
    else if(vie->taille.x<=25)
        vie->barre.setFillColor(sf::Color(255,255,0));



}
