#include "World.h"

#include <iostream>
#include <cmath>

Player::Player()
{
    sprite.create("img/player.png", {8, 8});
}

void Player::init(World& world)
{
    this->world = &world;
}

void Player::onKeyPressed(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::W:
        nextMove = sf::Vector2f(0.f, -1.f);
        break;
    case sf::Keyboard::D:
        nextMove = sf::Vector2f(1.f, 0.f);
        break;
    case sf::Keyboard::S:
        nextMove = sf::Vector2f(0.f, 1.f);
        break;
    case sf::Keyboard::A:
        nextMove = sf::Vector2f(-1.f, 0.f);
        break;
    default:
        nextMove = sf::Vector2f(0.f, 0.f);
        break;
    }
}

void Player::update(sf::Time dt)
{
    if (notMoving())
    {
        if (world->isEmpty(pos + nextMove))
            move(nextMove);
        else 
            bump(nextMove);

        nextMove = sf::Vector2f(0.f, 0.f);
    }

    Entity::update(dt);
}
