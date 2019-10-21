#include "animation.hpp"

Animation initAnimation(float cadence, sf::Clock * clock)
{
    Animation nouveau;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Texture> textures;
    nouveau.temps = clock->getElapsedTime();
    nouveau.cadence = cadence;
    nouveau.sprites = sprites;
    nouveau.textures = textures;
    nouveau.image = 0;
    nouveau.imageH = 0;
    nouveau.imageV = 0;
    nouveau.px = 79;
    nouveau.py = 80;
    nouveau.position = 0;
    return nouveau;
}

void addSprite(Animation &animation, sf::Sprite sprite)
{
    animation.sprites.push_back(sprite);
}

void addSprite(Animation &animation, sf::Texture texture)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    animation.sprites.push_back(sprite);
}

void addTexture(Animation &animation, sf::Texture texture)
{


    animation.textures.push_back(texture);
    addSprite(animation, animation.textures[animation.textures.size()-1]);
}

void nextSpriteAnimation(Animation &animation)
{
    animation.image = (animation.image + 1)%animation.sprites.size();
}

sf::Sprite renderAnimation(Animation &animation,sf::Vector2f position, sf::Clock * clock)
{
    if(animation.temps.asSeconds() + (1.0/animation.cadence) < clock->getElapsedTime().asSeconds())
    {
        nextSpriteAnimation(animation);
        animation.temps = clock->getElapsedTime();
    }
    animation.sprites[animation.image].setPosition(position);
    return animation.sprites[animation.image];
}

sf::Sprite renderAnimationSpriteSheet(Animation *animation, sf::Vector2f *position, sf::Clock *clock, int sx, int sy)
{
    //79 8x6
    Sprite sprite;
    //printf("MDR");
    if (isExplosionAlive(*animation))
    {
        //printf("%f + %f < %f\n", animation->temps.asSeconds(), (1.0/animation->cadence), clock->getElapsedTime().asSeconds());
        //printf("%i %i %i %i %i %i\n", animation->image, animation->imageH, animation->imageV, animation->px, animation->py, animation->position);
        if(animation->temps.asSeconds() + (1.0/animation->cadence) < clock->getElapsedTime().asSeconds())
        {
            animation->temps = clock->getElapsedTime();
            animation->image += 1;
            //printf("%i\n", animation->image);
            if(animation->imageH < sx-1)
                animation->imageH += 1;
            else
            {
                animation->imageH = 0;
                if (animation->imageV < sy-1)
                    animation->imageV += 1;
                else
                    animation->imageV = 0;
            }
        }

        animation->intRect = IntRect(animation->imageH*animation->px,animation->imageV*animation->py, animation->px, animation->py);
        sprite = Sprite(animation->textures[0], animation->intRect);
        sprite.setOrigin(animation->sprites[0].getOrigin());
        sprite.setPosition(*position + Vector2f(-100,-100));
    }
    return sprite;
}

void initExplosions(Animation all_explosions[], Animation const& explosion, int nb)
{
    for(int i(0); i<nb; i++)
    {
        all_explosions[i] = explosion;
    }
}

bool isAvailable(Animation const& anim)
{
    if(anim.position != 0)
        return false;
    return true;
}

bool isExplosionAlive(Animation const& anim)
{
    if(anim.image < 48 && !isAvailable(anim))
        return true;
    return false;
}

int firstAvailableExplosion(Animation all[], int nb, int sx, int sy)
{
    for(int i(0); i<nb; i++)
    {
        if(isAvailable(all[i]))
            return i;
    }
    return -1;
}

void resetAnimation(Animation &anim)
{
    anim.image = 0;
    anim.imageH = 0;
    anim.imageV = 0;
    anim.position = 0;
    Clock clock;
    anim.temps = clock.getElapsedTime();
}

void resetAllAnimation(Animation all[])
{
    int i;
    for (i=0; i<256; i++)
    {
        resetAnimation(all[i]);
    }
}
