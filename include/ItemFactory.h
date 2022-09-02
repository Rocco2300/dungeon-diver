#pragma once

#include "Item.h"
#include "Player.h"

class ItemFactory
{
private:
    enum class Label
    {
        Name = 0,
        Type,
        Value,
        None = -1
    };

private:
    Player* player;

public:
    ItemFactory() = default;
    ItemFactory(Player& player);

    Item getItem();

private:
    ItemType stringToItemType(std::string type);
};