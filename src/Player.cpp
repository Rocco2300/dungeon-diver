#include "World.h"

#include <iostream>
#include <cmath>

Player::Player()
{
    hp = 5;

    sprite.create("img/player.png", {8, 8});
}

void Player::onKeyPressed(sf::Keyboard::Key key)
{
    if (!world->isPlayerTurn())
        return;

    switch (key)
    {
    case sf::Keyboard::W:
        moves.push_back(sf::Vector2i(0, -1));
        break;
    case sf::Keyboard::D:
        moves.push_back(sf::Vector2i(1, 0));
        break;
    case sf::Keyboard::S:
        moves.push_back(sf::Vector2i(0, 1));
        break;
    case sf::Keyboard::A:
        moves.push_back(sf::Vector2i(-1, 0));
        break;
    default:
        break;
    }
}

void Player::update(sf::Time dt)
{
    if (notMoving() && !moves.empty() && world->isPlayerTurn())
    {
        auto nextMove = moves.front();
        moves.erase(moves.begin());

        if (world->isOccupied(this, pos + nextMove))
            bump(nextMove);
        else if (world->isWall(this, pos + nextMove))
            bump(nextMove);
        else 
            move(nextMove);
        
        world->endTurn(this);
    }

    Entity::update(dt);
}
