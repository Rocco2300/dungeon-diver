#include "Spawner.h"

#include "World.h"

#include "ResourceHolder.h"

void Spawner::init(World& world)
{
    this->world = &world;
    this->entities = &this->world->getEntities();

    csv.load("csv/Enemies.csv");
}

void Spawner::spawnEnemy(sf::Vector2i pos)
{
    Entity* enemy = new Enemy();

    ResourceHolder<sf::Texture, std::string> holder;

    enemy->setWorld(*world);
    enemy->setHP(stoi(csv(0, Label::HP)));
    enemy->setDamage(stoi(csv(0, Label::DMG)));
    enemy->setSprite(holder, csv(0, Label::Path), csv(0, Label::Path).c_str(), {8, 8});
    enemy->setPosition(pos);

    entities->push_back(enemy);
}