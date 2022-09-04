#pragma once

#include <array>
#include <memory>
#include <vector>
#include <functional>

#include "Item.h"
#include "Entity.h"

class Player : public Entity
{
private:
    int selectedItem;
    std::array<std::unique_ptr<Item>, 5> inventory;

    std::vector<sf::Vector2i> moves;

public:
    Player();

    void giveItem(Item* item);

    void onKeyPressed(sf::Keyboard::Key key);
    void update(sf::Time dt);

private:
    void useItem();
    void printInventory();
};

