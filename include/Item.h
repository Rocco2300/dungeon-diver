#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Player;

enum class ItemType
{
    Heal,
    Damage,
    None = -1
};

class Item
{
public:
    using Ptr = std::unique_ptr<Item>;

private:
    Player* player;
    ItemType type;

    std::string name;

    sf::Sprite spr;

    int value;

public:
    Item() = default;
    Item(ItemType type, std::string name, int value, Player& player);

    void use();

    std::string getName();
};