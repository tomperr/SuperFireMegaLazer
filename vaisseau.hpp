#ifndef VAISSEAU_HPP_INCLUDED
#define VAISSEAU_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "bullet.hpp"

using namespace sf;

Vaisseau addVaisseau(Sprite sprite, Vector2f position, Vector2f velocity, int hp, int damage, Bullet bullet, float cadence, sf::Clock *clock, sf::Sprite sprites[]);
Vector2f deplacement(Event event);
void tirVaisseau(Enemy all_enemies[], Bullet all_bullets[], Vaisseau *vaisseau, Clock * clock, int *max_bullet);
void resetVaisseau(Vaisseau *vaisseau, Clock clock);


#endif // VAISSEAU_HPP_INCLUDED
