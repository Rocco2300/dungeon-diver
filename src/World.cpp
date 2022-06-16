#include "World.h"

#include <iostream>

void World::create(Tileset& tileset)
{
    // CSV<Label> csv("csv/Enemies.csv");
    // csv.print();

    nextLevel = false;

    gen.generateMap();
    auto stream    = gen.getMapAsStream();
    auto playerPos = gen.getEntrance();

    this->playerTurn = true;
    this->tileset = &tileset;

    map.setSize({16, 16});
    map.setTileset(*this->tileset);
    map.loadMap(stream);

    player.setWorld(*this);
    player.setPosition(playerPos);

    entities.push_back(&player);
    // spawner.init(*this);
    // spawner.spawnEnemy({7, 10});

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
        auto exitTile = dynamic_cast<ExitStairsTile*>(&map(posI));

        if (t)
        {
            t->onInteract();

            if (exitTile)
                nextLevel = true;
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
            {
                delete entities[i];
                entities.erase(entities.begin() + i);
            }

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

std::vector<Entity*>& World::getEntities()
{
    return entities;
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
    sf::Vector2i pos;
    std::stringstream stream;
    
    switch (key)
    {
    case sf::Keyboard::Comma:
        gen.printAreasArray();
        break;
    case sf::Keyboard::Period:
        gen.printWallsArray();
        break;
    case sf::Keyboard::Slash:
        gen.printSignatures();
        break;
    case sf::Keyboard::SemiColon:
        gen.printRoomMap();
        break;
    case sf::Keyboard::G:
        gen.generateMap();
        stream = gen.getMapAsStream();
        pos = gen.getEntrance();
        player.setPosition(pos);
        map.loadMap(stream);
        break;
    default:
        break;
    }

    player.onKeyPressed(key);
}

void World::update(sf::Time dt)
{
    if (entities.size() < 2)
        playerTurn = true;

    player.update(dt);
    for (size_t i = 0; i < entities.size(); i++)
    {
        auto enemy = dynamic_cast<Enemy*>(entities[i]);
        if (enemy)
        {
            enemy->update(dt);
        }
    }

    if (nextLevel)
    {
        gen.generateMap();
        auto stream = gen.getMapAsStream();
        auto pos = gen.getEntrance();
        player.setPosition(pos);
        map.loadMap(stream);
        nextLevel = false;
    }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(map, states);

    for (size_t i = 0; i < entities.size(); i++)
    {
        target.draw(*entities[i], states);
    }
}