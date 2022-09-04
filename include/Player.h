#pragma once

#include <functional>
#include <vector>

#include "Item.h"
#include "Entity.h"


class Player : public Entity
{
private:
    Item* item;

    std::vector<sf::Vector2i> moves;

public:
    Player();

    void giveItem(Item* item);

    void onKeyPressed(sf::Keyboard::Key key);
    void update(sf::Time dt);

private:
    void useItem();
};

