#include "Player.h"

Player::Player()
{
    input = -1;

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
    this->input = -1;
    this->pos = pos;
    
    off.x = 0;
    off.y = 0;

    spr = sf::RectangleShape({8.f, 8.f});
    spr.setPosition(pos.x * 8 + off.x, pos.x * 8 + off.x);
    spr.setFillColor(sf::Color::Green);
}

void Player::update(sf::Time dt)
{
    if (input != -1)
    {
        pos.x += dirX[input];
        pos.y += dirY[input];

        off.x = -dirX[input] * 8;
        off.y = -dirY[input] * 8;

        t = 0;
        input = -1;
    }

    spr.setPosition(pos.x * 8 + off.x, pos.y * 8 + off.y);

    t = std::min(t + dt.asSeconds() * 2, 1.f);

    off.x = off.x * (1 - t);
    off.y = off.y * (1 - t);

    if(t == 1)
        t = 0;
}

void Player::setInput(int input)
{
    this->input = input;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(spr, states);
}