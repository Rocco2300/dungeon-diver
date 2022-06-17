#pragma once

#include "AStar.h"
#include "Entity.h"

class World;

enum class AIState
{
    Idle,
    Chase
};

class Enemy : public Entity
{
private:
    AStar aStar;
    AIState state;

    sf::Time moveTime;

public:
    Enemy();

    AIState getState();

    void setWorld(World& world);

    void update(sf::Time dt);
private:
    int distToPlayer();
    bool playerLos();
};

