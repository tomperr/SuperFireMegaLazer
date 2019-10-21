#include "enemy.hpp"
#include "fonctions_bg.hpp"

//#include <SFML/Graphics.hpp>

using namespace sf;

/*
    Fonction qui renvoie une structure Enemy avec les caractéristiques données.
    NE PAS OUBLIER DE CORRIGER LA FONCTION POUR METTRE LE BULLET
    velocity correspond au pas
                                                                                */
Enemy addEnemy(Vector2f position, Sprite sprite, int hp, Vector2f velocity, int damage, Clock clock_notreset, Bullet bullet, float cadence, int score)
{
    // Creer un nouvel ennemi
    Enemy nouveau;
    nouveau.position = position;
    nouveau.sprite = sprite;
    //nouveau.sprite.rotate(180);
    nouveau.sprite.setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    nouveau.hp = hp;
    nouveau.velocity = velocity;
    nouveau.damage = damage;
    nouveau.temps = clock_notreset.getElapsedTime();
    nouveau.bullet = bullet;
    nouveau.cadence = cadence;
    nouveau.score = score;
    return nouveau;
}

int firstDeadEnemy(Enemy all[], int max_enemy)
{
    // Trouve le premier ennemie mort dans la liste de tous les ennemies
    int i;
    for (i=0; i<=max_enemy + 1; i++)
    {
        if (!isEnemyAlive(all[i]))
        {
            return i;
        }
    }
    return -1;
}

void appendEnemy(Enemy all[], Enemy nouveau, int *max_enemy)
{
    // Ajoute un ennemi a la liste de tous les ennemies
    int index = firstDeadEnemy(all, *max_enemy);
    if (index > *max_enemy)
    {
        *max_enemy = index;
    }
    all[index] = nouveau;
}

void resetAllEnemies(Enemy all[])
{
    // Reset tous les ennemies
    int i;
    for (i=0; i<NB_ENEMY; i++)
    {
        all[i].hp = 0;
    }
}

// Fonction de tir
void shootEnemy(Bullet all_bullets[], Enemy all_enemies[], Clock clock_notreset, Vector2f pos_vaisseau, int max_enemy, int *max_bullet)
{
    int i;
    for (i=0; i<=max_enemy; i++)
    {
        if (isEnemyAlive(all_enemies[i]))
        {
            if (all_enemies[i].temps.asSeconds() + (1.0/all_enemies[i].cadence) < clock_notreset.getElapsedTime().asSeconds())
            {
                Vector2f position;
                position.x = all_enemies[i].position.x - (all_enemies[i].sprite.getGlobalBounds().width + all_enemies[i].bullet.sprite.getGlobalBounds().width)/2;
                //position.x = all_enemies[i].position.x - all_enemies[i].bullet.sprite.getGlobalBounds().width;
                position.y = all_enemies[i].position.y + 1;

                Vector2f direction;
                direction.x = pos_vaisseau.x - all_enemies[i].position.x;
                direction.y = pos_vaisseau.y - all_enemies[i].position.y;
                if (all_enemies[i].position.y < pos_vaisseau.y)
                {

                    direction = Normalize(direction.x, direction.y);

                    Vector2f velocity;
                    velocity.x = all_enemies[i].bullet.velocity.x * direction.x;
                    velocity.y = all_enemies[i].bullet.velocity.y * direction.y;

                    Bullet nouveau = addBullet(all_enemies[i].bullet.sprite, position,
                                                velocity, all_enemies[i].damage, all_enemies[i].bullet.bulletType,
                                                all_enemies[i].bullet.isPlayerBullet);
                    appendBullet(all_bullets, nouveau, max_bullet);
                    all_enemies[i].temps = clock_notreset.getElapsedTime();
                }
            }
        }
    }
}

int isEnemyAlive(Enemy enemy) // and on screen
{
    // Verifie si l'ennemie est sur l'ecran
    int answer = 0;
    if (enemy.position.x < WINDOW_WIDTH && enemy.position.x - enemy.sprite.getGlobalBounds().width > 0
            && enemy.position.y - enemy.sprite.getGlobalBounds().height < WINDOW_HEIGHT && enemy.position.y + enemy.sprite.getGlobalBounds().height > -150)
    {
        if (enemy.hp > 0)
        {
            answer = 1;
        }
    }
    return answer;
}

void spawnEnemy(Enemy all_enemies[], Clock *clock, float delay, Clock clock_notreset, int *max_enemy, int *max_bullet, Enemy enemy_template[])
{
    // Creer et fait apparaitre un ennemi sur l'ecran
    if (clock->getElapsedTime().asSeconds() > delay)
    {
        int random = (int)rand() % (100);
        int i = 0;
        if (random < ENEMY1_RATE)
            i=0;
        else if (random < ENEMY2_RATE)
            i=1;
        else if (random < ENEMY3_RATE)
            i=2;
        else if (random < ENEMY4_RATE)
            i=3;

        Sprite nouveau_sp = enemy_template[i].sprite;
        float nouveau_cadence = enemy_template[i].cadence;
        Bullet nouveau_bullet = enemy_template[i].bullet;
        int nouveau_damage = enemy_template[i].damage;
        int nouveau_hp = enemy_template[i].hp;
        int nouveau_score = enemy_template[i].score;

        Vector2f position;
        position.x = rand() % (int)(WINDOW_WIDTH-nouveau_sp.getGlobalBounds().width);
        position.y = -100;

        Vector2f velocity;
        velocity.x = 0;
        velocity.y = rand() % (150) + 100;

        Enemy nouveau = addEnemy(position, nouveau_sp, nouveau_hp, velocity, nouveau_damage, clock_notreset, nouveau_bullet, nouveau_cadence, nouveau_score);
        appendEnemy(all_enemies, nouveau, max_enemy);

        clock->restart();
    }
}
