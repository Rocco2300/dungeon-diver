#pragma once

#include "Tile.h"
#include "InteractableTile.h"

class DoorTile : public Tile, public InteractableTile
{
private:
    
public:
    DoorTile() = default;

    void onInteract();
};
