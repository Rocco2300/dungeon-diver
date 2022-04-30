#include "World.h"

World::World()
{
}

void World::create(Tileset& tileset)
{
    this->tileset = &tileset;

    map.setSize({16, 16});
    map.setTileset(*this->tileset);
    map.loadMap("map.txt");

    player.init(*this);
}

bool World::isWall(sf::Vector2f pos)
{
    return !map((int)pos.x, (int)pos.y).isWalkable();
}

void World::keyPressed(sf::Keyboard::Key key)
{
    player.onKeyPressed(key);
}

void World::update(sf::Time dt)
{
    player.update(dt);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(map);
    target.draw(player, states);
}