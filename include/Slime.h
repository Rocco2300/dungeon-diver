#pragma once

#include "Entity.h"

class World;

class Slime : public Entity
{
private:
    World* world;

    sf::Time moveTime;
public:
    Slime();
    void init(World& world);

    void update(sf::Time dt);
private:
    bool playerLos();
};

