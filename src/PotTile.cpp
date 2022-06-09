#include "PotTile.h"

void PotTile::onInteract()
{
    if (!interactable)
        return;

    spriteID = 1;
    walkable = true;
    interactable = false;
}