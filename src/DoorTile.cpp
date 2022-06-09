#include "DoorTile.h"

void DoorTile::onInteract()
{
    if (!interactable)
        return;

    spriteID = 1;
    walkable = true;
    interactable = false;
}
