#include "Tile.h"

Tile::Tile()
{
}

int Tile::getID()
{
    return spriteID;
}

bool Tile::isWalkable()
{
    return walkable;
}

void Tile::setTileset(Tileset& tileset)
{
    this->tileset = &tileset;
}

void Tile::setID(int spriteID)
{
    this->spriteID = spriteID;
}

void Tile::setWalkable(bool walkable)
{
    this->walkable = walkable;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    tileset->setSpriteIndex(spriteID);
    target.draw(*tileset, states);
}