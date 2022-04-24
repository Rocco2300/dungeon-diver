#include "Player.h"

#include <iostream>
#include <cmath>

Player::Player()
{
    flip = 1.f;
    frame = 0.f;

    pos.x = 0.f;
    pos.y = 0.f;

    sprite.create("img/player.png", {8, 8});

    animation = std::bind(&Player::animateBump, this);
}

Player::Player(sf::Vector2f pos)
{
    flip = 1.f;
    frame = 0.f;

    this->pos = pos;

    sprite.create("img/player.png", {8, 8});

    animation = std::bind(&Player::animateBump, this);
}

void Player::move(sf::Vector2f o)
{
    if (t != 1)
        return;

    pos.x += o.x;
    pos.y += o.y;

    offS.x = -o.x * 8;
    offS.y = -o.y * 8;

    off = offS;

    t = 0;

    if (o.x != 0)
        flip = o.x;

    animation = std::bind(&Player::animateMove, this);
}

void Player::bump(sf::Vector2f o)
{
    if (t != 1)
        return;
        
    offS.x = o.x * 8;
    offS.y = o.y * 8;

    off = offS;

    t = 0;

    if (o.x != 0)
        flip = o.x;

    animation = std::bind(&Player::animateBump, this);
}

void Player::update(sf::Time dt)
{
    frame += dt.asSeconds() * 5;

    sprite.setSpriteIndex((int)std::floor(frame) % 3);

    if (t != 1)
    {
        animate(dt.asSeconds() * 8);
    }
}

bool Player::notMoving()
{
    return (t == 1);
}

sf::Vector2f Player::getPosition()
{
    return pos;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform transform;
    transform.translate(pos.x * 8 + off.x, pos.y * 8 + off.y);
    transform.scale({flip, 1.f}, {4.f, 4.f});
    states.transform = transform;

    target.draw(sprite, states);
}

void Player::animate(float animationSpeed)
{
    t = std::min(t + animationSpeed, 1.f);

    animation();
}

void Player::animateMove()
{
    off.x = offS.x * (1 - t);
    off.y = offS.y * (1 - t);
}

void Player::animateBump()
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