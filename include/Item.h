#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "Player.h"

enum class ItemType
{
    Heal,
    Damage,
    None = -1
};

class Item
{
private:
    Player* player;
    ItemType type;

    std::string name;

    sf::Sprite spr;

    int value;

public:
    Item() = default;
    Item(ItemType type, std::string name, Player& player);

    void use();
};