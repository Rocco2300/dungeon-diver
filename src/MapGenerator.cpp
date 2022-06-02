#include "MapGenerator.h"

#include <iostream>
#include <random>

MapGenerator::MapGenerator()
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            walls[index(x, y)] = 1;
        }
    }
}

sf::Vector2i MapGenerator::getRandomRoom()
{
    sf::Vector2i res;
    res.x = rand() % 3 + 3;
    res.y = rand() % 3 + 3;

    return res;
}

bool MapGenerator::canPlaceRoom(sf::Vector2i pos, sf::Vector2i room)
{
    for (int y = 0; y < room.y; y++)
    {
        for (int x = 0; x < room.x; x++)
        {
            if (walls[index(pos.x + x, pos.y + y)] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

bool MapGenerator::placeRoom(sf::Vector2i room)
{
    sf::Vector2i randPos(rand() % (16 - room.x), rand() % (16 - room.y));

    if (canPlaceRoom(randPos, room))
    {
        for (int y = 0; y < room.y; y++)
        {
            for (int x = 0; x < room.x; x++)
            {
                walls[index(randPos.x + x, randPos.y + y)] = 0;
            }
        }

        return true;
    }

    return false;
}

int MapGenerator::index(int x, int y)
{
    return y * 16 + x;
}

void MapGenerator::printWallsArray()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            std::cout << walls[index(j, i)] << " ";
        }

        std::cout << '\n';
    }
}