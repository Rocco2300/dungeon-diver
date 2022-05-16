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

    sf::Vector2f pos;
    sf::Vector2f offS;
    sf::Vector2f off;

    int hp;
    bool dead;
public:
    Entity();   
    void init(World& world);

    int getHp();
    bool isDead();

    void takeDamage(int damageAmount);
    void setPosition(sf::Vector2f pos);

    void move(sf::Vector2f o);
    void bump(sf::Vector2f o);

    bool notMoving();
    sf::Vector2f getPosition();

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    void animate(float animationSpeed);
    void animateMove();
    void animateBump();
};
