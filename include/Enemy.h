#pragma once

#include "Entity.h"

class World;

class Enemy : public Entity
{
protected:
    sf::Time moveTime;

public:
    Enemy();

    virtual ~Enemy() = default;

protected:
    bool playerLos();
};

