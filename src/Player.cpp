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

void Player::move(int dir)
{
    if (finished)
    {
        pos.x += dirX[dir];
        pos.y += dirY[dir];

        offS.x = -dirX[dir] * 8;
        offS.y = -dirY[dir] * 8;

        off.x = offS.x;
        off.y = offS.y;

        t = 0;
        finished = false;

        if (dirX[dir] != 0)
            spr.setScale(dirX[dir], 1.f);
    }
    else 
        dirBuf.push_back(dir);
}

void Player::update(sf::Time dt)
{
    if (!dirBuf.empty() && finished)
    {
        auto mov = dirBuf.front();
        dirBuf.erase(dirBuf.begin());

        move(mov);
    }

    frame += dt.asSeconds() * 4;

    spr.setPosition(pos.x * 8 + off.x, pos.y * 8 + off.y);
    spr.setTextureRect({{(int)std::floor(frame) % 3 * 8, 0}, {8, 8}});

    animate(dt.asSeconds() * 8);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(spr, states);
}

void Player::animate(float animationSpeed)
{
    if (!finished)
    {
        t = std::min(t + animationSpeed, 1.f);

        off.x = offS.x * (1 - t);
        off.y = offS.y * (1 - t);

        if(t == 1)
        {
            t = 0;
            finished = true;
        }
    }
}