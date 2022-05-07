#pragma once

#include "Tile.h"
#include "InteractableTile.h"

class ChestTile : public Tile, public InteractableTile
{
private:
    
public:
    ChestTile();

    void onInteract();
};
