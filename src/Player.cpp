#include "World.h"

#include <iostream>
#include <cmath>

#include "AssetManager.h"

Player::Player() : item{nullptr}
{
    hp = 5;
    damage = 1;

    sprite.create(AssetManager::getTexture("player"), {8, 8});
}

void Player::giveItem(Item *item)
{
    this->item = item;
}

void Player::onKeyPressed(sf::Keyboard::Key key)
{
    if (!world->isPlayerTurn())
        return;

    switch (key)
    {
    case sf::Keyboard::W:
        moves.emplace_back(0, -1);
        break;
    case sf::Keyboard::D:
        moves.emplace_back(1, 0);
        break;
    case sf::Keyboard::S:
        moves.emplace_back(0, 1);
        break;
    case sf::Keyboard::A:
        moves.emplace_back(-1, 0);
        break;
    case sf::Keyboard::U:
        useItem();
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

void Player::useItem()
{
    if (item)
    {
        item->use();
        delete item;
        item = nullptr;
    }
}