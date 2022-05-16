#pragma once

#include <functional>
#include <vector>

#include "Entity.h"

class Player : public Entity
{
private:
    std::vector<sf::Vector2f> moves;

public:
    Player();

    void onKeyPressed(sf::Keyboard::Key key);
    void update(sf::Time dt);
};

