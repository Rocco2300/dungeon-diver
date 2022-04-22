#include "Player.h"

Player::Player()
{
    finished = false;

    pos.x = 0;
    pos.y = 0;

    off.x = 0;
    off.y = 0;

    spr = sf::RectangleShape({8.f, 8.f});
    spr.setPosition(pos.x * 8 + off.x, pos.x * 8 + off.x);
    spr.setFillColor(sf::Color::Green);
}

Player::Player(sf::Vector2f pos)
{
    finished = false;

    this->pos = pos;
    
    off.x = 0;
    off.y = 0;

    spr = sf::RectangleShape({8.f, 8.f});
    spr.setPosition(pos.x * 8 + off.x, pos.x * 8 + off.x);
    spr.setFillColor(sf::Color::Green);
}

void Player::move(int dir)
{
    if (finished)
    {
        pos.x += dirX[dir];
        pos.y += dirY[dir];

        off.x = -dirX[dir] * 8;
        off.y = -dirY[dir] * 8;

        t = 0;
        finished = false;
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

    spr.setPosition(pos.x * 8 + off.x, pos.y * 8 + off.y);

    t = std::min(t + dt.asSeconds() * 2, 1.f);

    off.x = off.x * (1 - t);
    off.y = off.y * (1 - t);

    if(t == 1)
    {
        t = 0;
        finished = true;
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(spr, states);
}