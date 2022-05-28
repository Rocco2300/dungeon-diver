
#include "Entity.h"

#include <iostream>
#include <cmath>

#include "World.h"

Entity::Entity()
{
    t = 1.f;
    flip = 1.f;
    frame = 0.f;

    pos.x = 0.f;
    pos.y = 0.f;

    dead = false;
}

void Entity::init(World& world)
{
    this->world = &world;
}

int Entity::getHp()
{
    return hp;
}

bool Entity::isDead()
{
    return dead;
}

void Entity::takeDamage(int damageAmount)
{
    hp -= damageAmount;

    if (hp <= 0)
        dead = true;
}

void Entity::setPosition(sf::Vector2i pos)
{
    this->pos = pos;
}

void Entity::move(sf::Vector2i o)
{
    if (t != 1)
        return;

    pos += o;

    offS.x = -o.x * 8;
    offS.y = -o.y * 8;

    off = offS;

    t = 0;

    if (o.x != 0)
        flip = o.x;

    animation = std::bind(&Entity::animateMove, this);
}

void Entity::bump(sf::Vector2i o)
{
    if (t != 1)
        return;
        
    offS.x = o.x * 8;
    offS.y = o.y * 8;

    off = offS;

    t = 0;

    if (o.x != 0)
        flip = o.x;

    animation = std::bind(&Entity::animateBump, this);
}

void Entity::update(sf::Time dt)
{
    if (dead)
        return;

    frame += dt.asSeconds() * 5;

    sprite.setSpriteIndex((int)std::floor(frame) % 3);

    if (t != 1)
    {
        animate(dt.asSeconds() * 8);
    }
}

bool Entity::notMoving()
{
    return (t == 1);
}

sf::Vector2i Entity::getPosition()
{
    return pos;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (dead)
        return;
        
    sf::Transform transform;
    transform.translate(pos.x * 8 + off.x, pos.y * 8 + off.y);
    transform.scale({flip, 1.f}, {4.f, 4.f});
    states.transform = transform;

    target.draw(sprite, states);
}

void Entity::animate(float animationSpeed)
{
    t = std::min(t + animationSpeed, 1.f);

    animation();
}

void Entity::animateMove()
{
    off.x = offS.x * (1 - t);
    off.y = offS.y * (1 - t);
}

void Entity::animateBump()
{
    if (t < 0.5f)
    {
        off.x = offS.x * t;
        off.y = offS.y * t;
    }
    else
    {
        off.x = offS.x * (1 - t);
        off.y = offS.y * (1 - t);
    }
}