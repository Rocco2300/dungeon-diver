#pragma once

#include <vector>

#include "Enemy.h"
#include "CSV.h"

class World;

class Spawner
{
private:
    enum class Label
    {
        Name = 0,
        HP,
        DMG,
        None = -1
    };

    CSV<Label> csv;

    World* world;
    std::vector<Entity*>* entities;

public:
    Spawner();
    void init(World& world);

    void spawnEnemy(sf::Vector2i pos);
};
