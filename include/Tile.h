#pragma once

#include "Tileset.h"

class Tile : public sf::Drawable
{
protected:
    sf::RectangleShape debugRect;
    Tileset* tileset;

    int spriteID;
    bool debug;
    bool walkable;

public:
    Tile();

    int getID();
    bool isWalkable();

    void setDebug(bool debug);
    void setDebugRect(sf::Color color, int alpha);
    void setTileset(Tileset& tileset);
    void setID(int spriteID);
    void setWalkable(bool walkable);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

