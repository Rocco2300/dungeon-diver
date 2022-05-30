#include "Spawner.h"

#include "World.h"

void Spawner::init(World& world)
{
    this->world = &world;
    this->entities = &this->world->getEntities();

    csv.load("csv/Enemies.csv");
}

void Spawner::spawnEnemy(sf::Vector2i pos)
{
    Enemy* enemy = new Enemy();

}