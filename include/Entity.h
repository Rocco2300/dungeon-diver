#pragma once

#include <functional>
#include <vector>

#include "Tileset.h"

class World;

class Entity : public sf::Drawable
{
protected:
    World* world;

    float t;
    float flip;
    float frame;
    
    Tileset sprite;
    sf::Sprite currFrame;

    std::function<void()> animation;

    sf::Vector2i pos;
    sf::Vector2f offS;
    sf::Vector2f off;

    int hp;
    int damage;
    bool dead;
public:
    Entity();   
    virtual void setWorld(World& world);

    int getHp();
    bool isDead();

    void setHP(int hp);
    void setDamage(int damage);
    void setSprite(const char* path, sf::Vector2i size);
    void setSprite(ResourceHolder<sf::Texture, std::string>& resourceHolder, std::string id,
        const char* path, sf::Vector2i tileSize);
    void takeDamage(int damageAmount);
    void setPosition(sf::Vector2i pos);

    void move(sf::Vector2i o);
    void bump(sf::Vector2i o);

    bool notMoving();
    sf::Vector2i getPosition();

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    void animate(float animationSpeed);
    void animateMove();
    void animateBump();
};
