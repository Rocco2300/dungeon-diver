#include "ChestTile.h"

ChestTile::ChestTile()
{
}

void ChestTile::onInteract()
{
    if (!interactable)
        return;
        
    spriteID += 1;
    interactable = false;
}