#include "draw.hpp"
#include "enemy.hpp"
#include "powerup.hpp"
#include "animation.hpp"

void draw(RenderWindow *app, Enemy enemy)
{
    // Affiche un ennemi
    app->draw(enemy.sprite);
}

void draw(RenderWindow *app, Bullet bullet)
{
    // Affiche une balle
    app->draw(bullet.sprite);
}

void draw(RenderWindow *app, Animation *explosion, Clock * clock)
{
    // Affiche une animation
    app->draw(renderAnimationSpriteSheet(explosion,explosion->position,clock,8,6));
}

void draw(RenderWindow *app, Background *bg)
{
    // Affiche une couche de l'arriere plan
    app->draw(bg->sp1);
    app->draw(bg->sp2);
}

void draw(RenderWindow *app, Vaisseau *vaisseau)
{
    // Affiche le vaisseau du joueur
    app->draw(vaisseau->sprite);
}

void draw(RenderWindow *app, PowerUp *powerup)
{
    // Affiche une ammelioration
    if (isPowerupAlive(*powerup))
        app->draw(powerup->sprite);
}

void draw(RenderWindow *app, Vie *vie)
{
    // Affiche la barre de vie
    RectangleShape barre_background(Vector2f(100,20));
    barre_background.setFillColor(Color::Red);
    barre_background.setPosition(Vector2f(0,0));
    app->draw(barre_background);
    app->draw(vie->barre);
}

void move(Enemy *enemy, Time elapsed)
{
    // Calcule la position d'un ennemi
    enemy->position.x += enemy->velocity.x * elapsed.asSeconds();
    enemy->position.y += enemy->velocity.y * elapsed.asSeconds();
    enemy->sprite.setPosition(enemy->position.x, enemy->position.y);
}

void move(Bullet *bullet, Time elapsed)
{
    // Calcule la position d'une balle
    bullet->position.x += bullet->velocity.x * elapsed.asSeconds();
    bullet->position.y += bullet->velocity.y * elapsed.asSeconds();
    bullet->sprite.setPosition(bullet->position.x, bullet->position.y);
}

void move(Background *mon_bg, Time elapsed)
{
    // Calcule la position d'une couche de l'arriere plan
    mon_bg->position1.y += mon_bg->velocity.y * elapsed.asSeconds();
    mon_bg->position2.y += mon_bg->velocity.y * elapsed.asSeconds();

    if (mon_bg->position1.y > WINDOW_HEIGHT)
    {
        mon_bg->position1.y = mon_bg->position2.y - mon_bg->sp1.getGlobalBounds().height - mon_bg->between_sprite;
    }

    if (mon_bg->position2.y > WINDOW_HEIGHT)
    {
        mon_bg->position2.y = mon_bg->position1.y - mon_bg->sp1.getGlobalBounds().height - mon_bg->between_sprite;
    }

    mon_bg->sp1.setPosition(mon_bg->position1);
    mon_bg->sp2.setPosition(mon_bg->position2);
}

void move(Vaisseau *vaisseau, Time elapsed, Background mes_bg[])
{
    // Calcule la position du vaisseau
    // Déplacement horizontal (teste de collisions avec les bords de la fenetre)
    if (vaisseau->position.x + vaisseau->velocity.x * vaisseau->direction.x * elapsed.asSeconds() > 0
            && vaisseau->position.x + vaisseau->velocity.x * vaisseau->direction.x * elapsed.asSeconds() + vaisseau->sprite.getGlobalBounds().width < WINDOW_WIDTH)
    {
        vaisseau->position.x += vaisseau->velocity.x * vaisseau->direction.x * elapsed.asSeconds();
        // Parallaxe
        int i;
        for (i=0; i<NB_BACKGROUND; i++)
        {
            mes_bg[i].position1.x += mes_bg[i].velocity.x * elapsed.asSeconds() * (-vaisseau->direction.x);
            mes_bg[i].position2.x += mes_bg[i].velocity.x * elapsed.asSeconds() * (-vaisseau->direction.x);

        }
    }

    // Déplacement vertical (teste de collisions avec les bords de la fenetre)
    if (vaisseau->position.y + vaisseau->velocity.y * vaisseau->direction.y * elapsed.asSeconds() > 0
            && vaisseau->position.y + vaisseau->velocity.y * vaisseau->direction.y * elapsed.asSeconds() + vaisseau->sprite.getGlobalBounds().width < WINDOW_HEIGHT)
    {
        vaisseau->position.y += vaisseau->velocity.y * vaisseau->direction.y * elapsed.asSeconds();
        // Parallaxe
        int i;
        for (i=0; i<NB_BACKGROUND; i++)
        {
            mes_bg[i].position1.y += (mes_bg[i].velocity.y * elapsed.asSeconds() * (-vaisseau->direction.y))/2;
            mes_bg[i].position2.y += (mes_bg[i].velocity.y * elapsed.asSeconds() * (-vaisseau->direction.y))/2;

        }
    }

    vaisseau->sprite.setPosition(vaisseau->position);
}

void move(PowerUp *powerUp, Time elapsed)
{
    // Calcule la position d'une ammelioration
    if (isPowerupAlive(*powerUp))
    {
        powerUp->position.x += powerUp->velocity.x * elapsed.asSeconds();
        powerUp->position.y += powerUp->velocity.y * elapsed.asSeconds();
        powerUp->sprite.setPosition(powerUp->position);
    }
}

void manage(RenderWindow *app, Enemy all_enemies[], Time elapsed, int max_enemy)
{
    // Affiche et calcul tous les ennemies
    int i;
    for (i=0; i<=max_enemy; i++)
    {
        // Si l'ennemi est sur la fenetre et est vivant
        if (isEnemyAlive(all_enemies[i]))
        {
            // on calcule sa position
            move(&all_enemies[i], elapsed);
            // on l'affiche
            draw(app, all_enemies[i]);
        }
    }
}

void manage(RenderWindow *app, Bullet all_bullets[], Time elapsed, int max_bullet, Clock * clock)
{
    // Affiche et calcul toutes les balles
    int i;
    for (i=0; i<=max_bullet; i++)
    {
        switch(all_bullets[i].bulletType)
        {
        case Normal:
            // Si la bullet est sur la fenetre
            if (isBulletAlive(all_bullets[i]))
            {
                // on calcule sa position
                move(&all_bullets[i], elapsed);
                // on l'affiche
                draw(app, all_bullets[i]);
            }
            break;
        case Laser:
            if(isBulletAlive(all_bullets[i], clock))
            {
                // on calcule sa position
                move(&all_bullets[i], elapsed);
                // on l'affiche
                draw(app, all_bullets[i]);
            }
            else
            {
                all_bullets[i].position = Vector2f(-100,-100);
                all_bullets[i].sprite.setScale(Vector2f(1,1));
                all_bullets[i].sprite.setPosition(all_bullets[i].position);
            }
            break;
        }
    }
}

void manage(RenderWindow *app, Vaisseau *vaisseau, Time elapsed, Background mes_bg[], Sound gameOver)
{
    // Affiche et calcul le vaisseau du joueur
    if (vaisseau->hp > 0)
    {
        move(vaisseau, elapsed, mes_bg);
        draw(app, vaisseau);
    }
    else
    {
        gameOver.play();
    }
}

void manage(RenderWindow *app, PowerUp all[], Time elapsed)
{
    // Affiche et calcul toutes les ammeliorations
    int i;
    for (i=0; i<NB_POWERUP; i++)
    {
        if (isPowerupAlive(all[i]))
        {
            move(&all[i], elapsed);
            draw(app, &all[i]);
        }
    }
}

void manage(RenderWindow *app, Background all[], Time elapsed)
{
    // Affiche et calcul toutes les couches de l'arriere plan
    int i;
    for (i=0; i<NB_BACKGROUND; i++)
    {
        move(&all[i], elapsed);
        draw(app, &all[i]);
    }
}

void manage(RenderWindow *app, Animation all[], Clock *clock)
{
    // Affiche et calcul toutes les animations
    int i;
    for (i=0; i<256; i++)
    {
        if (isExplosionAlive(all[i]))
        {
            draw(app, &all[i], clock);
        }
        else if (all[i].position != 0)
        {
            resetAnimation(all[i]);
        }
    }
}
