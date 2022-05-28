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

void Tile::setDebug(bool debug)
{
    this->debug = debug;
}

void Tile::setDebugRect(sf::Color color, int alpha)
{
    debugRect = sf::RectangleShape({8, 8});
    color.a = alpha;
    debugRect.setFillColor(color);
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
    if (debug)
        target.draw(debugRect, states);
    target.draw(*tileset, states);
}