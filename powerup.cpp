#include "powerup.hpp"
#include "fonctions_bg.hpp"

void addBonus(Vaisseau *vaisseau, Bonus powerup)
{
    // Ajoute un bonus au vaisseau du joueur
    sf::Vector2f scale;
    switch(powerup)
    {
    case Damage:
        vaisseau->damage*=damageBonus;
        vaisseau->bullet.damage = vaisseau->damage;
        break;
    case FirePower:
        scale = vaisseau->bullet.sprite.getScale();
        scale.x *= firepowerBonus;
        scale.y *= firepowerBonus;
        vaisseau->bullet.sprite.setScale(scale);
        break;
    case FireRate:
        vaisseau->cadence *= firerateBonus;
        break;
    case BulletSpeed:
        Vector2f velocity = vaisseau->bullet.velocity;
        velocity.x *= bulletspeedBonus;
        velocity.y *= bulletspeedBonus;
        vaisseau->bullet.velocity = velocity;
        break;
    }
}

PowerUp addPowerUp(Sprite sprite, Bonus powerup, Vector2f position, Vector2f velocity)
{
    // Creer une ammelioration
    PowerUp nouveau;

    nouveau.sprite = sprite;
    nouveau.powerup = powerup;
    nouveau.velocity = velocity;
    nouveau.position = position;

    return nouveau;
}

PowerUp addPowerUp(Sprite sprite, Bonus powerup, Vector2f position)
{
    // Creer une ammelioration avec une velocite aleatoire
    PowerUp nouveau;

    nouveau.sprite = sprite;
    nouveau.powerup = powerup;

    //RANDOMIZATION de la velocité
    Vector2f velocity(0,0);
    velocity.x = rand()%POWERUP_SPEED;
    if (rand()%2 == 1)
    {
        velocity.x *= -1;
    }

    velocity.y = rand()%POWERUP_SPEED + POWERUP_SPEED/2;

    nouveau.velocity = velocity;
    nouveau.position = position;
    return nouveau;
}

int isPowerupAlive(PowerUp powerup)
{
    // Verifie si uen ammelioration est sur l'ecran
    int answer = 0;
    if (powerup.position.x + powerup.sprite.getGlobalBounds().width > 0 && powerup.position.x  < WINDOW_WIDTH &&
        powerup.position.y + powerup.sprite.getGlobalBounds().height > 0 && powerup.position.y < WINDOW_HEIGHT)
    {
        answer = 1;
    }
    return answer;
}

int firstDeadPowerup(PowerUp all[])
{
    // Cherche la premiere ammelioration "morte" dans la liste de toutes les ammeliorations
    int i;
    for (i=0; i<NB_POWERUP; i++)
    {
        if (!isPowerupAlive(all[i]))
        {
            return i;
        }
    }
    return -1;
}

void resetAllPowerup(PowerUp all[])
{
    // Reinitialise toutes les ammeliorations
    int i;
    for (i=0; i<NB_POWERUP; i++)
    {
        all[i].position.x = -100;
        all[i].position.y = -100;
    }
}

void appendPowerup(PowerUp all[], PowerUp nouveau)
{
    // Ajoute une ammelioration a la liste de toutes les ammeliorations
    int index = firstDeadPowerup(all);
    all[index] = nouveau;
}

void spawnPowerup(PowerUp all[], Sprite sprites[], Vector2f position)
{
    // Creer et fait apparaitre une ammelioration sur l'ecran
    int random = (int)rand() % 4;
    Sprite nouveau_sprite = sprites[random];
    PowerUp nouveau_powerup = addPowerUp(nouveau_sprite, Bonus(random), position);
    appendPowerup(all, nouveau_powerup);
}

void initPowerupTexture(Texture all[])
{
    // Gere les texture des ammeliorations
    if (!all[0].loadFromFile("img/powerup/damageup.png"))
        printf("Erreur de chargement de /img/powerup/damageup.png\n");

    if (!all[1].loadFromFile("img/powerup/bulletsize.png"))
        printf("Erreur de chargement de /img/powerup/bulletsize.png\n");

    if (!all[2].loadFromFile("img/powerup/firerate.png"))
        printf("Erreur de chargement de /img/powerup/firerate.png\n");

    if (!all[3].loadFromFile("img/powerup/bulletspeed.png"))
        printf("Erreur de chargement de /img/powerup/bulletspeed.png\n");
}

void initPowerupSprites(Sprite sp_powerup[], Texture all_texture[])
{
    // Gere les sprites des ammelioration
    sp_powerup[0] = Sprite(all_texture[0]);
    sp_powerup[1] = Sprite(all_texture[1]);
    sp_powerup[2] = Sprite(all_texture[2]);
    sp_powerup[3] = Sprite(all_texture[3]);
}

