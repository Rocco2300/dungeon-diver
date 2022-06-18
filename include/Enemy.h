#pragma once

#include "AStar.h"
#include "Entity.h"

class World;

enum class AIState
{
    Idle,
    Chase,
    Investigate
};

class Enemy : public Entity
{
private:
    AStar aStar;
    AIState state;

    sf::Vector2i playerPos;
    sf::Time moveTime;

public:
    Enemy();

    AIState getState();

    void setWorld(World& world);

    void updateState();
    void followPlayer();
    void update(sf::Time dt);
private:
    int distToPlayer();
    bool playerLos();
};

