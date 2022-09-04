#include "World.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "AssetManager.h"

Player::Player() : inventory{}
{
    hp = 5;
    damage = 1;

    sprite.create(AssetManager::getTexture("player"), {8, 8});
}

void Player::giveItem(Item *item)
{
    auto it = std::find(inventory.begin(), inventory.end(), nullptr);

    if (it != inventory.end())
    {
        *it = std::unique_ptr<Item>(item);
    }
}

std::array<std::unique_ptr<Item>, 5>& Player::getItemsRef()
{
    return inventory;
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
