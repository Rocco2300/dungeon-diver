#pragma once

#include <functional>
#include <vector>

#include "Entity.h"

class Player : public Entity
{
public:
    Player();

    void update(sf::Time dt);
};

