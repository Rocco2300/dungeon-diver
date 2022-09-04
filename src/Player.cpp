#include "World.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "AssetManager.h"

Player::Player() : selectedItem{-1}, inventory{}
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

        if (selectedItem == -1)
        {
            selectedItem = it - inventory.begin();
        }
    }
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
        printInventory();
        break;
    case sf::Keyboard::P:
        printInventory();
        break;
    case sf::Keyboard::RBracket:
        selectedItem = (selectedItem + 1) % 5;
        printInventory();
        break;
    case sf::Keyboard::LBracket:
        selectedItem = (selectedItem + 4) % 5;
        printInventory();
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
    if (selectedItem != -1 && inventory[selectedItem])
    {
        inventory[selectedItem]->use();
        inventory[selectedItem].reset();
    }
}

void Player::printInventory()
{
    for (size_t i = 0; i < inventory.size(); i++)
    {
        auto item = inventory[i].get();
        auto itemSlot = (item) ? item->getName() : "Empty";

        std::stringstream ss;
        if (i == selectedItem)
            ss << '[' << std::left << itemSlot << "] ";
        else
            ss << ' ' << std::left << itemSlot << "  ";

        std::cout << std::left << std::setw(10) << ss.str();
    }
    std::cout << std::endl;
}