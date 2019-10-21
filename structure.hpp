#ifndef STRUCTURE_HPP_INCLUDED
#define STRUCTURE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

using namespace sf;

enum BulletType { Normal, Laser }; // Type de balle envoye par le vaisseau du joueur
enum Bonus { Damage, FirePower, FireRate, BulletSpeed }; // Type d'ammeliorations que peuvent generer les enemies

typedef struct {
    // Structure qui gere les animations
    sf::Time temps;
    float cadence;
    int image;
    int imageH;
    int imageV;
    int px;
    int py;
    Vector2f * position;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Texture> textures;
    IntRect intRect;
} Animation;

typedef struct
{
    // Structure pour les bullets
    Sprite sprite;
    Vector2f position;
    Vector2f velocity;
    float damage;
    BulletType bulletType;
    Time temps;
    bool isPlayerBullet;
} Bullet;

typedef struct
{
    // Structure pour les enemies
    Vector2f position;
    Sprite sprite;
    Vector2f velocity;
    int hp;
    int damage;
    Time temps;
    Bullet bullet;
    float cadence;
    int score;
} Enemy;

typedef struct
{
    // Structure qui gère le vaisseau du joueur
    float cadence;
    float default_cadence;
    Vector2f position;
    Vector2f velocity;
    Vector2f direction;
    Time temps;
    Sprite sprite;
    int hp;
    int full_hp;
    int damage;
    int default_damage;
    Bullet bullet;
    Bullet default_bullet;
    Animation thrusters;
} Vaisseau;

typedef struct
{
    // Structure qui gère une couche de l'arriere plan
    Texture image;
    Sprite sp1;
    Sprite sp2;
    Vector2f position1;
    Vector2f position2;
    Vector2f velocity;
    int between_sprite;
} Background;

struct PowerUp
{
    // Structure qui gère une ammelioration
    Sprite sprite;
    Bonus powerup;
    Vector2f position;
    Vector2f velocity;
};

#endif // STRUCTURE_HPP_INCLUDED
