#pragma once

#include "Tile.h"
#include "InteractableTile.h"

class PotTile : public Tile, public InteractableTile
{
private:
    
public:
    PotTile() = default;

    void onInteract();
};
