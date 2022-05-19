#pragma once

#include <vector>

struct Cell 
{
    int _fCost;
    int _gCost;
    int _hCost;
    std::vector<Cell*> neighbours;

    Cell();
    int fCost();
    int gCost();
    int hCost();
};

class NavMap
{
private:
    std::vector<Cell> cells;
public:
    NavMap();

    void addNeighbours(int x, int y);
};


