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

    void setHook(bool value);
    void giveItem(Item* item);

    void onKeyPressed(sf::Keyboard::Key key);
    void update(sf::Time dt);

protected:
    void endTurn();

private:
    void handleMove(sf::Vector2i nextMove);
    void handleAttack(sf::Vector2i nextMove);
    void handleWallBump(sf::Vector2i nextMove);
};
