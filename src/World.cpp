#include "World.h"

#include <iostream>

#include "SoundManager.h"

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
    spawner.init(*this);
    // spawner.spawnEnemy({7, 10});

    std::vector<sf::Vector2i> openTiles;
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        if (map(x, y).isWalkable())
            openTiles.push_back({x, y});
    }

    for (int i = 0; i < 2; i++)
    {
        auto idx = rand() % openTiles.size();
        spawner.spawnEnemy({openTiles[idx].x, openTiles[idx].y});
        openTiles.erase(openTiles.begin() + idx);
    }

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

        if (t)
        {
            t->onInteract();

            auto exitTile = dynamic_cast<ExitStairsTile*>(t);
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

            SoundManager::playSound("sound/hit1.wav");

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
    static std::vector<Entity*> toMove;

    if (entity == &player)
    {
        playerTurn = false;

        toMove.clear();
        for (size_t i = 0; i < entities.size(); i++)
        {
            if (entities[i] != &player)
                toMove.push_back(entities[i]);
        }
        // DEBUG
        // for (int i = 0; i < 16; i++)
        // {
        //     for (int j = 0; j < 16; j++)
        //     {
        //         map(i, j).setDebug(false);
        //     }
        // }
    }
    else 
    {
        auto it = std::find(toMove.begin(), toMove.end(), entity);
        if (it != toMove.end())
        {
            toMove.erase(it);
        }

        if (toMove.empty())
            playerTurn = true;
    }
}

void World::keyPressed(sf::Keyboard::Key key)
{
    sf::Vector2i pos;
    std::stringstream stream;
    
    // @Debugging
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

    if (nextLevel && player.notMoving())
    {
        gen.generateMap();
        auto stream = gen.getMapAsStream();
        auto pos = gen.getEntrance();
        player.setPosition(pos);
        map.loadMap(stream);
        nextLevel = false;
    }

    // Remove sounds that finished playing
    SoundManager::cleanSounds();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(map, states);

    for (size_t i = 0; i < entities.size(); i++)
    {
        target.draw(*entities[i], states);
    }
}