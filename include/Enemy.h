#pragma once

#include "AStar.h"
#include "Entity.h"

class World;



class Enemy : public Entity
{
protected:
    AStar aStar;

    sf::Time moveTime;

public:
    Enemy();

    virtual ~Enemy() = default;

protected:

    bool playerLos();
};

