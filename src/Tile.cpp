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

bool Tile::isInteractable()
{
    return interactable;
}

TileType Tile::getTileType()
{
    return tileType;
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

void Tile::setInteractable(bool interactable)
{
    this->interactable = interactable;
}

void Tile::setTileType(TileType tileType)
{
    this->tileType = tileType;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    tileset->setSpriteIndex(spriteID);
    target.draw(*tileset, states);
}