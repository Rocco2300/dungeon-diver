#include "World.h"

#include <algorithm>
#include <iomanip>

#include "AssetManager.h"

Player::Player()
    : inventory{}
{
    hp     = 5;
    damage = 1;
    hook   = false;

    sprite.create(AssetManager::getTexture("player"), {8, 8});
}

void Player::setHook(bool value) { hook = value; }

void Player::giveItem(Item* item)
{
    auto it = std::find(inventory.begin(), inventory.end(), nullptr);

    if (it != inventory.end()) { *it = std::unique_ptr<Item>(item); }
}

ItemContainer& Player::getItemsRef() { return inventory; }

void Player::onKeyPressed(sf::Keyboard::Key key)
{
    if (!world->canMove(this)) return;

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
    if (notMoving() && !moves.empty() && world->canMove(this))
    {
        auto nextMove = moves.front();
        moves.erase(moves.begin());

        if (world->isOccupied(pos + nextMove))
        {
            bump(nextMove);
            world->attack(this, pos + nextMove);
        }
        else if (world->isWall(pos + nextMove))
        {
            bump(nextMove);
            world->interact(this, pos + nextMove);
        }
        else
        {
            if (hook)
            {
                int i = 0;
                while (!world->isWall(pos + i * nextMove)) { i++; }

                move((i - 1) * nextMove);
                hook = false;
            }
            else
                move(nextMove);
        }

        world->endTurn(this);
    }

    Entity::update(dt);
}
