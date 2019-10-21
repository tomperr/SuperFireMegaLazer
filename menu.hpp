#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ostream>
#define TAILLE_FENETRE 750
#define HAUTEUR_FENETRE 550
#define HAUTEUR_FENETREVAISSEAU 500

using namespace sf;

typedef struct
{
    Sprite sprite;
    Sprite spriteTitre;
    Font font;
    Text textMenu[4];
    Color color;
    int pointeur = 0;
    bool wait = false;
} Menu;

typedef struct
{
    Sprite background;

    Sprite texSelect; //triangle

    Sprite SpriteVaisseau [4];
    Text textVaisseau [4];

    int pointeur = 0;
    int pointeurArmes = 0;
    Font font;

    bool escape = false; //bool pour savoir quand entrée pressed si retour au menu ou non.
    bool choixArmes = false;
    unsigned int choix = 0;

}StructFenVaisseau;

typedef struct
{
    Sprite spriteOptions;
    Text textOptions[4];
    RectangleShape barreSon;
    RectangleShape curseurSon;
    Font font;
    int curseurX = 645, curseurY = 95;
    int indicateurVolume = 100;
    int pointeur = 0;
    unsigned int choixVolume = 0;
    bool choixVolumeMusique = false;

}StructFenOptions;

void changementChoix(Menu &menu, Event event);
Menu addMenu(Font font, Text textMenu[], Sprite sprite, Sprite spriteTitre, Music music[]);
void drawMenu(RenderWindow *appMenu, Menu menu, Event event);
void selection(Event event,Menu menu, RenderWindow *appMenu, RenderWindow *fenetreVaisseau, RenderWindow *fenetreOptions, Music music[], bool *veutJouer);

StructFenVaisseau imVaisseau(Sprite background, Sprite vaisseau[], Sprite TexSelect, Text textVaisseau[]);
void choixDuVaisseau(StructFenVaisseau &vaisseau, Event event, RenderWindow *fenetreVaisseau, RenderWindow *appMenu);
void drawFenetreVaisseau(RenderWindow *fenetreVaisseau, StructFenVaisseau vaisseau, Event event);

StructFenOptions imageOptions(Sprite imOptions, Text textOptions[], RectangleShape barreSon, RectangleShape curseurSon, Font font, int pointeur);
void choixOptions(StructFenOptions &fenOptions, Event event, RenderWindow *fenetreOptions, RenderWindow *appMenu);
void drawFenetreOptions(RenderWindow *fenetreOptions, StructFenOptions options, Event event);

#endif // MENU_HPP_INCLUDED
