#include "World.h"

#include <iostream>

World::World()
{
}

void World::create(Tileset& tileset)
{
    this->playerTurn = true;
    this->tileset = &tileset;

    map.setSize({16, 16});
    map.setTileset(*this->tileset);
    map.loadMap("map.txt");

    player.setWorld(*this);
    slime.setWorld(*this);
    slime.setPosition({7, 7});

    entities.push_back(&player);
    entities.push_back(&slime);

    moveTime = sf::seconds(.3f);
}

bool World::isWall(Entity* caller, sf::Vector2i pos)
{
    if (pos.x < 0 || pos.x > 15 || pos.y < 0 || pos.y > 15)
        return true;

    sf::Vector2i posI(pos.x, pos.y);

    auto returnVal = !map(posI).isWalkable();

    if (caller == &player)
    {
        auto t = dynamic_cast<InteractableTile*>(&map(posI));

        if (t != nullptr)
        {
            t->onInteract();
        }
    }

    return returnVal;
}

bool World::isOccupied(Entity* caller, sf::Vector2i pos)
{
    for (int i = entities.size()-1; i >= 0; i--)
    {
        if (pos == entities[i]->getPosition())
        {
            // If we use this function in another context
            // ouside of entity interaction don't damage entities
            if (caller == nullptr)
                return true;

            entities[i]->takeDamage(1);

            if (entities[i]->isDead())
                entities.erase(entities.begin() + i);

            return true;
        }
    }
    return false;
}

bool World::isPlayerTurn()
{
    return playerTurn;
}

sf::Vector2i World::getPlayerPos()
{
    return player.getPosition();
}

void World::endTurn(Entity* entity)
{
    if (entity == &player)
    {
        playerTurn = false;

        // @Debugging
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                map(i, j).setDebug(false);
            }
        }
    }
    else 
        playerTurn = true;
}

void World::keyPressed(sf::Keyboard::Key key)
{
    player.onKeyPressed(key);
}
void World::update(sf::Time dt)
{
    if (entities.size() < 2)
        playerTurn = true;

    player.update(dt);
    if (!slime.isDead())
        slime.update(dt);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(map, states);
    target.draw(slime, states);
    target.draw(player, states);
}