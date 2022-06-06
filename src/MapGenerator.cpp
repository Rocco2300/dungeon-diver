#include "MapGenerator.h"

#include <iostream>
#include <random>

#include "Constants.h"

MapGenerator::MapGenerator()
{
    walls.resize(16*16);

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            Cell cell;
            walls[index(x, y)] = cell;
        }
    }
}

void MapGenerator::generateMap()
{
    generateRooms();
    carveMaze();
}

void MapGenerator::generateRooms()
{
    for (int i = 0; i < 5; i++)
    {
        auto room = getRandomRoom();
        placeRoom(room);
    }

    updateMapSignatures();
}

void MapGenerator::updateMapSignatures()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            updateSignature(j, i);
            updateNeighbouringSignatures(j, i);
        }
    }
}

void MapGenerator::carveMaze()
{
    std::vector<sf::Vector2i> candidates;

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (walls[index(x, y)].isWall && walls[index(x, y)].signature == 255)
            {
                candidates.push_back({x, y});
            }
        }
    }

    if (!candidates.empty())
    {
        int idx = rand() % candidates.size();

        carveCoridor(candidates[idx]);
    }
}

void MapGenerator::carveCoridor(sf::Vector2i start)
{
    int dir = rand() % 4; // Get a random cardinal direction
    int dx = dirX[dir], dy = dirY[dir];

    walls[index(start.x, start.y)].isWall = false;

    while (isCarvable(start.x + dx, start.y + dy))
    {
        walls[index(start.x + dx, start.y + dy)].isWall = false;

        updateMapSignatures();

        start.x += dx;
        start.y += dy;
    }
}

std::stringstream MapGenerator::getMapAsStream()
{
    std::stringstream res;

    for (size_t i = 0; i < walls.size(); i++)
    {
        int tile = (walls[i].isWall) ? 2 : 1;

        // @Debugging
        int x = i % 16;
        int y = i / 16;
        tile = (isCarvable(x, y)) ? 11 : tile;
        
        res << tile << " ";
    }

    return res;
}

Room MapGenerator::getRandomRoom()
{
    Room res;

    sf::Vector2i size;

    // 3 - 7
    size.x = rand() % 5 + 3;
    size.y = rand() % 5 + 3;

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

            if (!walls[index(room.pos.x + x, room.pos.y + y)].isWall)
            {
                return false;
            }
        }
    }

    return true;
}

bool MapGenerator::placeRoom(Room& room)
{
    room.pos = sf::Vector2i(rand() % (16 - room.size.x), rand() % (16 - room.size.y));

    int cnt = 0;
    while (!findFreeSpot(room))
    {
        if (cnt == 3)
            return false;

        shrinkRoom(room);
        cnt ++;
    }

    carveOutRoom(room);

    return true;
}

void MapGenerator::printWallsArray()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            std::cout << walls[index(j, i)].isWall << " ";
        }

        std::cout << '\n';
    }
}

void MapGenerator::printSignatures()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            std::cout << (int)walls[index(j, i)].signature << " ";
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

bool MapGenerator::isCarvable(int x, int y)
{
    if (!isInBounds(x, y) || !walls[index(x, y)].isWall)
        return false;

    for (size_t i = 0; i < mask.size(); i++)
    {   
        auto sig = walls[index(x, y)].signature;

        if ((sig | mask[i]) == (match[i] | mask[i]))
            return true;
    }

    return false;
}

bool MapGenerator::findFreeSpot(Room& room)
{
    int cnt = 0;
    while (!canPlaceRoom(room))
    {
        if (cnt == 100)
        {
            std::cout << "Failed to place room!" << std::endl;
            return false;
        }

        room.pos.x = rand() % (16 - room.size.x);
        room.pos.y = rand() % (16 - room.size.y);

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
            walls[index(room.pos.x + x, room.pos.y + y)].isWall = false;
        }
    }
}

void MapGenerator::updateSignature(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        if (isInBounds(dirX[i] + x, dirY[i] + y))
            walls[index(x, y)].signature |= (int)walls[index(dirX[i] + x, dirY[i] + y)].isWall << i;
        else 
            walls[index(x, y)].signature |= 1 << i;


        if (isInBounds(diagX[i] + x, diagY[i] + y))
            walls[index(x, y)].signature |= (int)walls[index(diagX[i] + x, diagY[i] + y)].isWall << (i + 4);
        else 
            walls[index(x, y)].signature |= 1 << (i + 4);
    }
}

void MapGenerator::updateNeighbouringSignatures(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        if (isInBounds(dirX[i] + x, dirY[i] + y))
            updateSignature(dirX[i] + x, dirY[i] + y);
        
        if (isInBounds(diagX[i] + x, diagY[i] + y))
            updateSignature(diagX[i] + x, diagY[i] + y);
    }
}

void MapGenerator::shrinkRoom(Room& room)
{
    room.size.x = (room.size.x > 3) ? room.size.x - 1 : 3;
    room.size.y = (room.size.y > 3) ? room.size.y - 1 : 3;
}