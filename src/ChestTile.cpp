#include "ChestTile.h"

void ChestTile::onInteract()
{
    if (!interactable)
        return;
        
    spriteID += 1;
    interactable = false;
}