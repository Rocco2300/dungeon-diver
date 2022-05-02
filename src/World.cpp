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

    player.init(*this);
    slime.init(*this);
    slime.move({1.f, 0.f});

    entities.push_back(&player);
    entities.push_back(&slime);

    moveTime = sf::seconds(.3f);
}

bool World::isWall(Entity* caller, sf::Vector2f pos)
{
    if (pos.x < 0 || pos.x > 15 || pos.y < 0 || pos.y > 15)
        return true;

    sf::Vector2i posI((int)pos.x, (int)pos.y);

    auto returnVal = !map(posI).isWalkable();

    if (caller == &player)
    {
        if (map(posI).isInteractable())
        {
            auto type = map(posI).getTileType();

            if (type == TileType::SmallChest || 
                type == TileType::LargeChest)
            {
                map(posI).setInteractable(false);

                auto ID = map(posI).getID();
                map(posI).setID(ID+1);
            }
            else if (type == TileType::Vase)
            {
                map(posI).setInteractable(false);
                map(posI).setWalkable(true);
                map(posI).setID(1);
            }
        }
    }

    return returnVal;
}

bool World::isOccupied(Entity* caller, sf::Vector2f pos)
{
    for (int i = entities.size()-1; i >= 0; i--)
    {
        if (pos == entities[i]->getPosition())
        {
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

void World::endTurn(Entity* entity)
{
    if (entity == &player)
        playerTurn = false;
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