#include "NavMap.h"

#include "Constants.h"

Cell::Cell() 
{
    neighbours.resize(4);

    _fCost = 0;
    _gCost = 0;
    _hCost = 0;
}

int Cell::fCost() { return _fCost; }
int Cell::gCost() { return _gCost; }
int Cell::hCost() { return _hCost; }

NavMap::NavMap() 
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            Cell cell;
            cells.push_back(cell);
        }
    }

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            addNeighbours(i, j);
        }
    }
}

void NavMap::addNeighbours(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        if (dirX[i] >= 0 && dirX[i] < 16 && dirY[i] >= 0 && dirY[i] < 16)
        {
            int currIdx = y * 16 + x;
            int neighbourIdx = dirY[i] * 16 + dirX[i];
            cells[currIdx].neighbours.push_back(&cells[neighbourIdx]);
        }
    }
}