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
    float tDmg;
    float flip;
    float frame;

    Tileset    sprite;
    sf::Sprite currFrame;
    sf::Shader shader;

    std::function<void()> animation;

    sf::Vector2i pos;
    sf::Vector2f offS;
    sf::Vector2f off;

    int  hp;
    int  damage;
    bool dead;

public:
    Entity();
    virtual void setWorld(World& world);

    int  getHp();
    int  getDamage();
    bool isDead();

    void setHP(int hp);
    void setDamage(int damage);
    void setSprite(std::string path, sf::Vector2i size);
    void takeDamage(int damageAmount);
    void setPosition(sf::Vector2i pos);

    void move(sf::Vector2i o);
    void bump(sf::Vector2i o);

    bool         notMoving();
    sf::Vector2i getPosition();

    virtual void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    virtual void endTurn();

private:
    void animate(float animationSpeed);
    void animateMove();
    void animateBump();
};
