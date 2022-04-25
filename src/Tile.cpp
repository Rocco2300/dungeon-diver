#include "Tile.h"

Tile::Tile()
{
}

int Tile::getID()
{
    return tileID;
}

bool Tile::isWalkable()
{
    return walkable;
}

bool Tile::isInteractable()
{
    return interactable;
}

void Tile::setTileset(Tileset& tileset)
{
    this->tileset = &tileset;
}

void Tile::setID(int tileID)
{
    this->tileID = tileID;
}

void Tile::setWalkable(bool walkable)
{
    this->walkable = walkable;
}

void Tile::setInteractable(bool interactable)
{
    this->interactable = interactable;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    tileset->setSpriteIndex(tileID);
    target.draw(*tileset, states);
}