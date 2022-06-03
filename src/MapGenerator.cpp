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
    for (int i = 0; i < 6; i++)
    {
        auto room = getRandomRoom();
        placeRoom(room);
    }
}

Room MapGenerator::getRandomRoom()
{
    Room res;

    sf::Vector2i size;
    size.x = rand() % 3 + 3;
    size.y = rand() % 3 + 3;

    res.size = size;

    return res;
}

bool MapGenerator::canPlaceRoom(Room room)
{
    for (int y = -1; y < room.size.y + 1; y++)
    {
        for (int x = -1; x < room.size.x + 1; x++)
        {
            // Consider out of bounds to be all walls
            if (!isInBounds(room.pos.x + x, room.pos.y + y))
                continue;

            if (walls[index(room.pos.x + x, room.pos.y + y)] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

bool MapGenerator::placeRoom(Room room)
{
    room.pos = sf::Vector2i(rand() % (16 - room.size.x) + 1, rand() % (16 - room.size.y) + 1);

    if (!findFreeSpot(room))
        return false;
        
    carveOutRoom(room);

    return true;
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

int MapGenerator::index(int x, int y)
{
    return y * 16 + x;
}

bool MapGenerator::isInBounds(int x, int y)
{
    return (x >= 0 && x < 16 && y >= 0 && y < 16);
}

bool MapGenerator::findFreeSpot(Room& room)
{
    int cnt = 0;
    while (!canPlaceRoom(room))
    {
        if (cnt == 1000)
        {
            std::cout << "Failed to place room!" << std::endl;
            return false;
        }

        room.pos.x = rand() % (14 - room.size.x) + 1;
        room.pos.y = rand() % (14 - room.size.y) + 1;

        cnt ++;
    }

    return true;
}

void MapGenerator::carveOutRoom(Room room)
{
    for (int y = 0; y < room.size.y; y++)
    {
        for (int x = 0; x < room.size.x; x++)
        {
            walls[index(room.pos.x + x, room.pos.y + y)] = 0;
        }
    }
}