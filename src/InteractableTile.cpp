#include "InteractableTile.h"

void ChestTile::onInteract()
{
    if (!interactable)
        return;
        
    spriteID += 1;
    interactable = false;
}

void DoorTile::onInteract()
{
    if (!interactable)
        return;

    spriteID = 1;
    walkable = true;
    interactable = false;
}

void PotTile::onInteract()
{
    if (!interactable)
        return;

    spriteID = 1;
    walkable = true;
    interactable = false;
}

void ExitStairsTile::onInteract()
{
    interactable = false;
}