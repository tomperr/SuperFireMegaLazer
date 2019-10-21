#include "vaisseau.hpp"
#include "fonctions_bg.hpp"
#include "animation.hpp"

Vector2f deplacement(Event event)
{
    // Gere les deplacements du joueur
    Vector2f direction(0,0);

    if (Keyboard::isKeyPressed(Keyboard::Left))
        direction.x += -1;

    if (Keyboard::isKeyPressed(Keyboard::Right))
        direction.x += 1;

    if (Keyboard::isKeyPressed(Keyboard::Up))
        direction.y += -1;

    if (Keyboard::isKeyPressed(Keyboard::Down))
        direction.y += 1;

    return direction;
}

Vaisseau addVaisseau(Sprite sprite, Vector2f position, Vector2f velocity, int hp, int damage, Bullet bullet, float cadence, sf::Clock *clock, sf::Sprite sprites[])
{
    // Creer le vaisseau du joueur
    Vaisseau nouveau;
    nouveau.sprite = sprite;
    nouveau.position = position;
    nouveau.sprite.setPosition(position);
    nouveau.velocity = velocity;
    nouveau.full_hp = hp;
    nouveau.hp = hp;
    nouveau.damage = damage;
    nouveau.default_damage = damage;
    nouveau.bullet = bullet;
    nouveau.default_bullet = bullet;
    nouveau.cadence = cadence;
    nouveau.default_cadence = cadence;
    nouveau.temps = clock->getElapsedTime();
    nouveau.thrusters = initAnimation(10, clock);
    addSprite(nouveau.thrusters, sprites[0]);
    addSprite(nouveau.thrusters, sprites[1]);
    addSprite(nouveau.thrusters, sprites[2]);
    addSprite(nouveau.thrusters, sprites[1]);
    return nouveau;
}

void tirVaisseau(Enemy all_enemies[], Bullet all_bullets[], Vaisseau *vaisseau, Clock * clock, int *max_bullet)
{
    // Gere les tirs du vaisseau
    if(Keyboard::isKeyPressed(Keyboard::Space))
    {
        if (vaisseau->temps.asSeconds() + (1.0/vaisseau->cadence) < clock->getElapsedTime().asSeconds())
        {
            Bullet nouveau = vaisseau->bullet;
            switch(vaisseau->bullet.bulletType)
            {
            case Normal: // pour les balles normales
                nouveau.position.x = vaisseau->position.x + (vaisseau->sprite.getGlobalBounds().width - vaisseau->bullet.sprite.getGlobalBounds().width)/2;
                nouveau.position.y = vaisseau->position.y - 30;
                appendBullet(all_bullets, nouveau, max_bullet);
                break;
            case Laser: // pour les laser
                if (vaisseau->bullet.bulletType == Laser)
                    nouveau.sprite.setOrigin(nouveau.sprite.getGlobalBounds().width, nouveau.sprite.getGlobalBounds().height);
                    laserToUp(vaisseau, all_enemies, &nouveau, clock, *max_bullet);
                    appendBullet(all_bullets, nouveau, max_bullet);
                break;
            }

            vaisseau->temps = clock->getElapsedTime();
        }
    }
}

void resetVaisseau(Vaisseau *vaisseau, Clock clock)
{
    // Reinitialise le vaisseau
    vaisseau->hp = vaisseau->full_hp;
    vaisseau->position = Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT-200);
    vaisseau->sprite.setPosition(Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT-200));
    vaisseau->cadence = vaisseau->default_cadence;
    vaisseau->bullet = vaisseau->default_bullet;
    vaisseau->damage = vaisseau->default_damage;
    vaisseau->temps = clock.getElapsedTime();
}
