#pragma once

#include "Enemy.h"

class World;

class Slime : public Enemy
{
public:
    Slime();

    void update(sf::Time dt);
};

