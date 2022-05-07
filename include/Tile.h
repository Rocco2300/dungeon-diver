#pragma once

#include "Tileset.h"

class Tile : public sf::Drawable
{
protected:
    Tileset* tileset;

    int spriteID;
    bool walkable;

public:
    Tile();

    int getID();
    bool isWalkable();

    void setTileset(Tileset& tileset);
    void setID(int spriteID);
    void setWalkable(bool walkable);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

