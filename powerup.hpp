#ifndef POWERUP_HPP_INCLUDED
#define POWERUP_HPP_INCLUDED

#include "vaisseau.hpp"
#include "structure.hpp"
#include <SFML/Graphics.hpp>

#define NB_POWERUP 8
#define damageBonus 1.1
#define firepowerBonus 1.1
#define firerateBonus 1.1
#define bulletspeedBonus 1.1
#define POWERUP_SPEED 100 // px par seconde

#define POWERUP_RATE 8 // en pourcentage

using namespace sf;

void addBonus(Vaisseau *vaisseau, Bonus powerup);
PowerUp addPowerUp(Sprite sprite, Bonus powerup, Vector2f position, Vector2f velocity);
PowerUp addPowerUp(Sprite sprite, Bonus powerup, Vector2f position);
int isPowerupAlive(PowerUp powerup);
int firstDeadPowerup(PowerUp all[]);
void resetAllPowerup(PowerUp all[]);
void appendPowerup(PowerUp all[], PowerUp nouveau);
void spawnPowerup(PowerUp all[], Sprite sprites[], Vector2f position);
void initPowerupTexture(Texture all_texture[]);
void initPowerupSprites(Sprite sp_powerup[], Texture all_texture[]);

#endif // POWERUP_HPP_INCLUDED
