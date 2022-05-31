#pragma once

#include "AStar.h"
#include "Entity.h"

class World;

class Enemy : public Entity
{
private:
    AStar aStar;

    sf::Time moveTime;

public:
    Enemy();

    void setWorld(World& world);

    void update(sf::Time dt);
private:
    int distToPlayer();
    bool playerLos();
};

