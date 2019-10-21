#include "fonctions_bg.hpp"

void initBackground(Background *mon_bg, char *path, Vector2f velocity, int between_sprite)
{
    // Initialise une couche de l'arriere plan
    if (!mon_bg->image.loadFromFile(path))
        printf("Erreur de chargement de %s\n", path);

    mon_bg->sp1.setTexture(mon_bg->image);
    mon_bg->sp2.setTexture(mon_bg->image);

    mon_bg->between_sprite = between_sprite;

    mon_bg->velocity = velocity;
    mon_bg->position1.x = (WINDOW_WIDTH - mon_bg->sp1.getGlobalBounds().width) / 2;
    mon_bg->position1.y = WINDOW_HEIGHT - mon_bg->sp1.getGlobalBounds().height;

    mon_bg->position2.x = mon_bg->position1.x;
    mon_bg->position2.y = mon_bg->position1.y - mon_bg->sp1.getGlobalBounds().height - between_sprite;

    mon_bg->sp1.setPosition(mon_bg->position1);
    mon_bg->sp2.setPosition(mon_bg->position2);
}
