#include "World.h"

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
    slime.move({1.f, 0.f});

    entities.push_back(&player);
    entities.push_back(&slime);

    moveTime = sf::seconds(1.f);
}

bool World::isWall(sf::Vector2f pos)
{
    if (pos.x < 0 || pos.x > 16 || pos.y < 0 || pos.y > 16)
        return true;

    return !map((int)pos.x, (int)pos.y).isWalkable();
}

bool World::isOccupied(Entity* caller, sf::Vector2f pos)
{
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (pos == entities[i]->getPosition())
            return true;
    }
    return false;
}

void World::keyPressed(sf::Keyboard::Key key)
{
    if (playerTurn)
    {
        player.onKeyPressed(key);
        playerTurn = false;

        moveTime = sf::seconds(1.f);
    }
}
void World::update(sf::Time dt)
{
    moveTime -= dt;

    if (!playerTurn & moveTime.asSeconds() <= 0)
    {
        int randDir;
        sf::Vector2f dirOff;

        do 
        {
            randDir = rand() % 4;

            dirOff = sf::Vector2f(dirX[randDir], dirY[randDir]);
        } while (isWall(slime.getPosition() + dirOff));

        if (isOccupied(&slime, slime.getPosition() + dirOff))
            slime.bump(dirOff);
        else
            slime.move(dirOff);
        playerTurn = true;
    }

    player.update(dt);
    slime.update(dt);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(map);
    target.draw(slime);
    target.draw(player, states);
}