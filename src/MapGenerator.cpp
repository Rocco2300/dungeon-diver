#include "MapGenerator.h"

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
    res.x = rand() % 5;
    res.y = rand() % 5;

    return res;
}

bool MapGenerator::placeRoom(sf::Vector2i room)
{
    sf::Vector2i randPos(rand() % (16 - room.x), rand() % (16 - room.y));

    for (int y = 0; y < room.y; y++)
    {
        for (int x = 0; x < room.x; x++)
        {
            if (walls[index(randPos.x + x, randPos.y + y)] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

int MapGenerator::index(int x, int y)
{
    return y * 16 + x;
}