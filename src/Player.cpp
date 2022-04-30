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
        moves.push_back(sf::Vector2f(0.f, -1.f));
        break;
    case sf::Keyboard::D:
        moves.push_back(sf::Vector2f(1.f, 0.f));
        break;
    case sf::Keyboard::S:
        moves.push_back(sf::Vector2f(0.f, 1.f));
        break;
    case sf::Keyboard::A:
        moves.push_back(sf::Vector2f(-1.f, 0.f));
        break;
    default:
        break;
    }
}

void Player::update(sf::Time dt)
{
    if (notMoving() && !moves.empty())
    {
        auto nextMove = moves.front();
        moves.erase(moves.begin());

        if (world->isOccupied(this, pos + nextMove))
            bump(nextMove);

        if (world->isWall(pos + nextMove))
            bump(nextMove);

        move(nextMove);
    }

    Entity::update(dt);
}
