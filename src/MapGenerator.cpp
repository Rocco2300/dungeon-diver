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

void MapGenerator::generateRooms()
{
    for (int i = 0; i < 3; i++)
    {
        auto room = getRandomRoom();
        placeRoom(room);
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
    for (int y = -1; y < room.y + 1; y++)
    {
        for (int x = -1; x < room.x + 1; x++)
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
    sf::Vector2i randPos(rand() % (14 - room.x) + 1, rand() % (14 - room.y) + 1);

    int cnt = 0;
    while (!canPlaceRoom(randPos, room))
    {
        if (cnt == 100)
            return false;

        randPos.x = rand() % (14 - room.x) + 1;
        randPos.y = rand() % (14 - room.y) + 1;

        cnt ++;
    }

    for (int y = 0; y < room.y; y++)
    {
        for (int x = 0; x < room.x; x++)
        {
            walls[index(randPos.x + x, randPos.y + y)] = 0;
        }
    }

    return true;
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