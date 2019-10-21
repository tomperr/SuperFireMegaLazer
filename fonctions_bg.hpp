#ifndef FONCTIONS_BG_HPP
#define FONCTIONS_BG_HPP

#include <SFML/Graphics.hpp>

#define NB_BACKGROUND 4
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#include "structure.hpp"

using namespace sf;

void initBackground(Background *mon_bg, char *path, Vector2f velocity, int between_sprite);

#endif // FONCTIONS_BG_HPP
