#include "Spawner.h"

#include "World.h"

void Spawner::init(World& world)
{
    this->world = &world;
    this->entities = &this->world->getEntities();

    csv.load(std::string(PROJ_PATH) + "csv/Enemies.csv");
}

void Spawner::spawnEnemy(sf::Vector2i pos)
{
    Entity* enemy = new Enemy();

    enemy->setWorld(*world);
    enemy->setHP(stoi(csv(0, Label::HP)));
    enemy->setDamage(stoi(csv(0, Label::DMG)));
    enemy->setSprite(csv(0, Label::Name), {8, 8});
    enemy->setPosition(pos);

    entities->push_back(enemy);
}