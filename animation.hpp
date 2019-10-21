#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

#include "structure.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

Animation initAnimation(float cadence, sf::Clock * clock);
void addSprite(Animation &animation, sf::Sprite sprite);
void addSprite(Animation &animation, sf::Texture texture);
void addTexture(Animation &animation, sf::Texture texture);
void nextSpriteAnimation(Animation &animation);
sf::Sprite renderAnimation(Animation &animation,sf::Vector2f position, sf::Clock * clock);
sf::Sprite renderAnimationSpriteSheet(Animation *animation, sf::Vector2f *position, sf::Clock *clock, int sx, int sy);
void initExplosions(Animation all_explosions[], Animation const& explosion, int nb);
bool isAvailable(Animation const& anim);
bool isExplosionAlive(Animation const& anim);
int firstAvailableExplosion(Animation all[], int nb, int sx, int sy);
void resetAnimation(Animation &anim);
void resetAllAnimation(Animation all[]);

#endif // ANIMATION_HPP_INCLUDED
