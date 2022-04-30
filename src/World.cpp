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
    slime.move({1.f, 0.f});
}

bool World::isWall(sf::Vector2f pos)
{
    return !map((int)pos.x, (int)pos.y).isWalkable();
}

bool World::isOccupied(Entity* caller, sf::Vector2f pos)
{
    return slime.getPosition() == pos;
}

void World::keyPressed(sf::Keyboard::Key key)
{
    player.onKeyPressed(key);
}

void World::update(sf::Time dt)
{
    player.update(dt);
    slime.update(dt);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(map);
    target.draw(slime);
    target.draw(player, states);
}