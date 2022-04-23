#include "Player.h"

#include <iostream>
#include <cmath>

Player::Player()
{
    frame = 0.f;
    finished = false;

    pos.x = .5f;
    pos.y = .5f;

    if (!tex.loadFromFile("img/player.png"))
        std::cerr << "Error loading player sprite!\n";

    spr.setTexture(tex);
    spr.setTextureRect(sf::IntRect({0, 0}, {8, 8}));
    spr.setOrigin(4.f, 4.f);
    spr.setPosition(pos.x * 8 + off.x, pos.x * 8 + off.x);

    animation = std::bind(&Player::animateBump, this);
}

Player::Player(sf::Vector2f pos)
{
    flip = false;
    frame = 0.f;
    finished = false;

    this->pos = pos;

    if (!tex.loadFromFile("img/player.png"))
        std::cerr << "Error loading player sprite!\n";

    spr.setTexture(tex);
    spr.setTextureRect(sf::IntRect({0, 0}, {8, 8}));
    spr.setOrigin(4.f, 4.f);
    spr.setPosition(pos.x * 8 + off.x, pos.x * 8 + off.x);
}

void Player::move(sf::Vector2f o)
{
    if (finished)
    {
        pos.x += o.x;
        pos.y += o.y;

        offS.x = -o.x * 8;
        offS.y = -o.y * 8;

        off.x = offS.x;
        off.y = offS.y;

        t = 0;
        finished = false;

        if (o.x != 0)
            spr.setScale(o.x, 1.f);
    }

    animation = std::bind(&Player::animateMove, this);
}

void Player::bump(sf::Vector2f o)
{
    if (finished)
    {
        offS.x = o.x * 8;
        offS.y = o.y * 8;

        off.x = offS.x;
        off.y = offS.y;

        t = 0;
        finished = false;

        if (o.x != 0)
            spr.setScale(o.x, 1.f);
    }

    animation = std::bind(&Player::animateBump, this);
}

void Player::update(sf::Time dt)
{
    frame += dt.asSeconds() * 5;

    spr.setTextureRect({{(int)std::floor(frame) % 3 * 8, 0}, {8, 8}});

    if (!finished)
    {
        animate(dt.asSeconds() * 8);
    }
    
    spr.setPosition(pos.x * 8 + off.x, pos.y * 8 + off.y);
}

bool Player::notMoving()
{
    return finished;
}

sf::Vector2f Player::getPosition()
{
    return pos;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(spr, states);
}

void Player::animate(float animationSpeed)
{
    t = std::min(t + animationSpeed, 1.f);

    animation();

    if(t == 1)
    {
        finished = true;
    }
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