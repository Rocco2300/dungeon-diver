#pragma once

#include <array>
#include <functional>
#include <memory>
#include <vector>

#include "Entity.h"
#include "ItemContainer.h"


class Player : public Entity
{
private:
    ItemContainer inventory;

    bool hook;

    std::vector<sf::Vector2i> moves;

public:
    Player();

    ItemContainer& getItemsRef();

    void giveItem(Item* item);

    void onKeyPressed(sf::Keyboard::Key key);
    void update(sf::Time dt);
};
