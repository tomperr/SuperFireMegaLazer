#include "bullet.hpp"
#include "fonctions_bg.hpp"

#include "enemy.hpp"

Bullet addBullet(Sprite sprite, Vector2f position, Vector2f velocity, float damage, BulletType bulletType, bool isPlayerBullet)
{
    // Genere une bullet
    Bullet bullet;
    bullet.sprite = sprite;
    bullet.position = position;
    bullet.velocity = velocity;
    bullet.damage = damage;
    bullet.sprite.setPosition(position);
    bullet.bulletType = bulletType;
    bullet.isPlayerBullet = isPlayerBullet;
    return bullet;
}

Vector2f Normalize(int x, int y)
{
    // Normalise un vecteur
    double norme = sqrt(x*x + y*y);
    return Vector2f(x/norme, y/norme);
}

void resetAllBullets(Bullet all[])
{
    // Reset toutes les bullets
    int i;
    for (i=0; i<NB_BULLETS; i++)
    {
        // Valeur par défaut pour que les bullets soient en dehors de l'écran
        all[i].position.x = WINDOW_WIDTH + 200;
        all[i].position.y = WINDOW_HEIGHT + 200;
    }
}

void appendBullet(Bullet all[], Bullet nouveau, int *max_bullet)
{
    // Ajoute une balle a la liste de toutes les balles
    int index = firstDeadBullet(all, *max_bullet);
    if (index > *max_bullet)
    {
        *max_bullet = index;
    }
    all[index] = nouveau;
}

int isBulletAlive(Bullet bullet)
{
    // Verifie si une balle est "en vie" = sur l'ecran
    int answer = 0;
    if (bullet.position.x + bullet.sprite.getGlobalBounds().width > 0 && bullet.position.x < WINDOW_WIDTH &&
        bullet.position.y + bullet.sprite.getGlobalBounds().height > 0 && bullet.position.y < WINDOW_HEIGHT)
    {
        answer = 1;
    }
    return answer;
}

int isBulletAlive(Bullet bullet, Clock * clock) // Lazer
{
    // Verifie si une balle est "en vie" (pour les lasers)
    int answer = 1;
    if(bullet.temps.asSeconds() + 0.2 <= clock->getElapsedTime().asSeconds())
    {
        answer = 0;
    }
    return answer;
}

int firstDeadBullet(Bullet all[], int max_bullet)
{
    // Regarde dans la liste de balles la premiere morte
    int i;
    for (i=0; i<=max_bullet + 1; i++)
    {
        if (!isBulletAlive(all[i]))
        {
            return i;
        }
    }
    return -1;
}

void laserToUp(Vaisseau * vaisseau, Enemy all_enemies[], Bullet *bullet, Clock * clock, int max_bullet)
{
    // Tire un laser
    int result(1200);
    bool isTouching = false;
    for(int i(0); i<=max_bullet; i++)
    {
        if(vaisseau->position.x < all_enemies[i].position.x - 50 &&
                vaisseau->position.x + vaisseau->sprite.getGlobalBounds().width > all_enemies[i].position.x - all_enemies[i].sprite.getGlobalBounds().width + 20 && vaisseau->position.y > all_enemies[i].position.y)
        {
            if(result > vaisseau->position.y - all_enemies[i].position.y)
                result = vaisseau->position.y - all_enemies[i].position.y + 20;
            bullet->sprite.setScale(Vector2f(1,result/vaisseau->bullet.sprite.getGlobalBounds().height));
            bullet->position = Vector2f(vaisseau->position.x + vaisseau->sprite.getGlobalBounds().width/2 + bullet->sprite.getGlobalBounds().width/2,vaisseau->position.y + 10);
            bullet->sprite.setPosition(vaisseau->bullet.position);

            isTouching = true;
        }
    }
    if(!isTouching)
    {
        bullet->sprite.setScale(Vector2f(1,result/vaisseau->bullet.sprite.getGlobalBounds().height));
        bullet->position = Vector2f(vaisseau->position.x + vaisseau->sprite.getGlobalBounds().width/2 + bullet->sprite.getGlobalBounds().width/2,vaisseau->position.y);
        bullet->sprite.setPosition(vaisseau->bullet.position);
    }
    bullet->damage = vaisseau->damage;
    bullet->temps = clock->getElapsedTime();
}

