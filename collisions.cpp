#include "collisions.hpp"
#include "powerup.hpp"
#include "fonctions_bg.hpp"
#include "animation.hpp"

int collisionBulletEnemyVaisseau(Bullet all_bullets[], Enemy all_enemies[], Vaisseau *vaisseau, int max_enemy, int max_bullet, PowerUp all_powerup[], Sprite sp_powerup[], Vie *vie, Animation all_explosions[])
{
    // Fonction pour gérer les collisions entre les balles et les enemies / le joueur
    int i, j;
    int score = 0;
    for (i=0; i<=max_bullet; i++)
    {
        if (isBulletAlive(all_bullets[i]))
        {
            if (all_bullets[i].isPlayerBullet)
            {
                for (j=0; j<=max_enemy; j++)
                {
                    if (isEnemyAlive(all_enemies[j]))
                    {
                        int first = 0;
                        switch(all_bullets[i].bulletType)
                        {
                        case Normal: // si une balle normale touche un enemi
                            if (all_bullets[i].sprite.getGlobalBounds().intersects(all_enemies[j].sprite.getGlobalBounds()))
                            {
                                // Penser à faire une fonction killBullet
                                all_bullets[i].position.x = WINDOW_WIDTH + 200;
                                all_bullets[i].position.y = WINDOW_HEIGHT + 200;
                                all_enemies[j].hp -= all_bullets[i].damage;
                                all_enemies[j].sprite.setColor(Color(255,0,0));
                                /*
                                first = firstAvailableExplosion(all_explosions, max_enemy, 8, 6);
                                resetAnimation(all_explosions[first]);
                                all_explosions[first].position = &all_enemies[j].position;
                                */
                            }
                            break;
                        case Laser: // si un laser touche un enemi
                            if (all_bullets[i].sprite.getGlobalBounds().intersects(all_enemies[j].sprite.getGlobalBounds()))
                            {
                                all_enemies[j].hp -= all_bullets[i].damage;
                                all_enemies[j].sprite.setColor(Color(255,0,0));
                                /*
                                first = firstAvailableExplosion(all_explosions, max_enemy, 8, 6);
                                resetAnimation(all_explosions[first]);
                                all_explosions[first].sprites[0].setOrigin(Vector2f(- all_enemies[j].sprite.getGlobalBounds().width/2 - all_explosions[first].sprites[0].getGlobalBounds().width/2, -all_enemies[j].sprite.getGlobalBounds().height));
                                all_explosions[first].position = &all_enemies[j].position;
                                */
                            }
                            break;
                        }


                        // Si l'ennemi est mort
                        if (all_enemies[j].hp <= 0)
                        {
                            first = firstAvailableExplosion(all_explosions, max_enemy, 8, 6);
                            resetAnimation(all_explosions[first]);
                            all_explosions[first].position = &all_enemies[j].position;

                            score += all_enemies[j].score;
                            int random = (int)rand() % 100;
                            if (random <= POWERUP_RATE)
                            {
                                // SPAWN POWERUP
                                spawnPowerup(all_powerup, sp_powerup, all_enemies[j].position);
                            }
                        }
                    }
                }
            }
            else
            {
                // Si une balle ennemie touche le vaisseau du joueur
                if (all_bullets[i].sprite.getGlobalBounds().intersects(vaisseau->sprite.getGlobalBounds()))
                {
                    vaisseau->hp -= all_bullets[i].damage;
                    changeBarreVie(vaisseau, vie);
                    all_bullets[i].position.x = WINDOW_WIDTH + 100;
                    all_bullets[i].position.y = WINDOW_HEIGHT + 100;
                }
            }
        }
    }
    return score;
}

void collisionVaisseauEnemy(Enemy all_enemies[], Vaisseau *vaisseau, int max_enemy)
{
    // Fonction qui gere les collisions entre les ennemies et le vaisseau du joueur
    int i;
    for (i=0; i<=max_enemy; i++)
    {
        if (isEnemyAlive(all_enemies[i]))
        {
            if (vaisseau->sprite.getGlobalBounds().intersects(all_enemies[i].sprite.getGlobalBounds()))
            {
                // Mort du perso
                vaisseau->hp = 0;
            }
        }
    }
}

void collisionVaisseauPowerup(PowerUp all_powerup[], Vaisseau *vaisseau)
{
    // Fonction qui gere les collisions entre les ammeliorations et le joueur
    int i;
    for (i=0; i<NB_POWERUP; i++)
    {
        if (isPowerupAlive(all_powerup[i]))
        {
            if (all_powerup[i].sprite.getGlobalBounds().intersects(vaisseau->sprite.getGlobalBounds()))
            {
                addBonus(vaisseau, all_powerup[i].powerup);
                all_powerup[i].position.x = -100;
                all_powerup[i].position.y = -100;
                all_powerup[i].sprite.setPosition(-100,-100);
            }
        }
    }
}
