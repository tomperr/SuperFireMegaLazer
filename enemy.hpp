#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#define NB_ENEMY 256
#define ENEMY1_RATE 30
#define ENEMY2_RATE 60
#define ENEMY3_RATE 80
#define ENEMY4_RATE 100

#define SCORE_ENEMY 100

#include "bullet.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Enemy addEnemy(Vector2f position, Sprite sprite, int hp, Vector2f velocity, int damage, Clock clock_notreset, Bullet bullet, float cadence, int score); //, Bullet bulletType
void appendEnemy(Enemy all[], Enemy nouveau, int *max_enemy);
void resetAllEnemies(Enemy all[]);
int firstDeadEnemy(Enemy all[], int max_enemy);
void shootEnemy(Bullet all_bullets[], Enemy all_enemies[], Clock clock_notreset, Vector2f pos_vaisseau, int max_enemy, int *max_bullet);
int isEnemyAlive(Enemy enemy); // and on screen
void spawnEnemy(Enemy all_enemies[], Clock *clock, float delay, Clock clock_notreset, int *max_enemy, int *max_bullet, Enemy enemy_template[]);

#endif // ENEMY_HPP_INCLUDED
