#ifndef DRAW_HPP_INCLUDED
#define DRAW_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "enemy.hpp"
#include "bullet.hpp"
#include "fonctions_bg.hpp"
#include "vaisseau.hpp"
#include "powerup.hpp"
#include "vie.hpp"

using namespace sf;

void draw(RenderWindow *app, Enemy all);
void draw(RenderWindow *app, Bullet bullet);
void draw(RenderWindow *app, Background *bg);
void draw(RenderWindow *app, Vaisseau *vaisseau);
void draw(RenderWindow *app, PowerUp *powerup);
void draw(RenderWindow *app, Vie *vie);
void draw(RenderWindow *app, Animation *explosion, Clock * clock);

void move(Enemy *all, Time elapsed);
void move(Bullet *bullet, Time elapsed);
void move(Background *mon_bg, Time elapsed);
void move(RenderWindow *app, Vaisseau *vaisseau, Time elapsed, Background mes_bg[]);
void move(PowerUp *powerUp, Time elapsed);

void manage(RenderWindow *app, Enemy all[], Time elapsed, int max_enemy);
void manage(RenderWindow *app, Bullet all[], Time elapsed, int max_bullet, Clock *clock);
void manage(RenderWindow *app, Vaisseau *vaisseau, Time elapsed, Background mes_bg[], Sound gameOver);
void manage(RenderWindow *app, PowerUp all[], Time elapsed);
void manage(RenderWindow *app, Background all[], Time elapsed);
void manage(RenderWindow *app, Animation all[], Clock *clock);

#endif // DRAW_HPP_INCLUDED
