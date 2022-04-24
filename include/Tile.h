#pragma once

#include "Tileset.h"

#include <functional>

class Tile : public sf::Drawable
{
private:
    Tileset* tileset;

    int tileID;

    bool walkable;
    bool interactable;

public:
    Tile();

    bool isWalkable();
    bool isInteractable();

    void setTileset(Tileset& tileset);
    void setID(int tileID);
    void setWalkable(bool walkable);
    void setInteractable(bool interactable);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

