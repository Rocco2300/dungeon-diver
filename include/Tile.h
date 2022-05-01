#pragma once

#include "Tileset.h"

enum TileType
{
    Deco,
    Wall,
    Door,
    SmallChest,
    LargeChest,
    Vase
};

class Tile : public sf::Drawable
{
private:
    Tileset* tileset;

    TileType tileType;

    int spriteID;

    bool walkable;
    bool interactable;

public:
    Tile();

    int getID();
    bool isWalkable();
    bool isInteractable();
    TileType getTileType();

    void setTileset(Tileset& tileset);
    void setID(int spriteID);
    void setWalkable(bool walkable);
    void setInteractable(bool interactable);
    void setTileType(TileType tileType);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

