#include "PotTile.h"

PotTile::PotTile()
{
    int id = rand() % 2 + 7;
    spriteID = id;
}

void PotTile::onInteract()
{
    spriteID = 1;
}