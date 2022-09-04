#pragma once

#include "Item.h"

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

    Item* getItem();
    void givePlayerItem();

private:
    ItemType stringToItemType(std::string type);
};