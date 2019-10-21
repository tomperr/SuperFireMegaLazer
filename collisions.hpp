#ifndef COLLISIONS_HPP_INCLUDED
#define COLLISIONS_HPP_INCLUDED

#include "bullet.hpp"
#include "enemy.hpp"
#include "vaisseau.hpp"
#include "powerup.hpp"
#include "vie.hpp"

int collisionBulletEnemyVaisseau(Bullet all_bullets[], Enemy all_enemies[], Vaisseau *vaisseau, int max_enemy, int max_bullet, PowerUp all_powerup[], Sprite sp_powerup[], Vie *vie, Animation all_explosions[]);
void collisionVaisseauEnemy(Enemy all_enemies[], Vaisseau *vaisseau, int max_enemy);
void collisionVaisseauPowerup(PowerUp all_powerup[], Vaisseau *vaisseau);

#endif // COLLISIONS_HPP_INCLUDED
