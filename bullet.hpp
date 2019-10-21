#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>
#include "structure.hpp"

#define NB_BULLETS 512
#define POSITION 100
#define PAS 1

using namespace sf;

Bullet addBullet(Sprite sprite, Vector2f position, Vector2f velocity, float damage, BulletType bulletType, bool isPlayerBullet);
Vector2f Normalize(int x, int y);
int firstDeadBullet(Bullet all[], int max_bullet);
int isBulletAlive(Bullet bullet);
int isBulletAlive(Bullet bullet, Clock * clock);
void resetAllBullets(Bullet all[]);
void appendBullet(Bullet all_bullet[], Bullet nouveau, int *max_bullet);
void laserToUp(Vaisseau * vaisseau, Enemy all_enemies[], Bullet *bullet, Clock * clock, int max_bullet);

#endif // BULLET_HPP_INCLUDED
