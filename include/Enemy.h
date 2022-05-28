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

public:
    int heuristic(sf::Vector2f curr, sf::Vector2f end);
    void aStar();
    void reconstructPath();
};

