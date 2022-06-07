#include "MapGenerator.h"

#include <iostream>
#include <iomanip>
#include <random>

#include "Constants.h"

MapGenerator::MapGenerator()
{
    walls.resize(16*16);

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            walls[index(x, y)] = true;
        }
    }

    areas.resize(16 * 16);
    for (size_t i = 0; i < areas.size(); i++)
    {
        areas[i] = -1;
    }
}

void MapGenerator::generateMap()
{
    generateRooms();
    carveMaze();
    fillAreas();
    carveDoors();
}

void MapGenerator::generateRooms()
{
    for (int i = 0; i < 4; i++)
    {
        auto room = getRandomRoom();
        placeRoom(room);
    }

    // updateMapSignatures();
}

// void MapGenerator::updateMapSignatures()
// {
//     std::cout << "here\n";

//     for (int i = 0; i < 16; i++)
//     {
//         for (int j = 0; j < 16; j++)
//         {
//             updateSignature(j, i);
//             updateNeighbouringSignatures(j, i);
//         }
//     }
// }

void MapGenerator::carveMaze()
{
    std::vector<sf::Vector2i> candidates;

    do 
    {
        candidates.clear();

        for (int y = 0; y < 16; y++)
        {
            for (int x = 0; x < 16; x++)
            {
                if (walls[index(x, y)] && getSignature(x, y) == 255)
                {
                    // carveStarts.insert({x, y});
                    candidates.push_back({x, y});
                }
            }
        }

        if (!candidates.empty())
        {
            int idx = rand() % candidates.size();

            carveCoridor(candidates[idx]);
        }

    } while (!candidates.empty());
}

uint8_t MapGenerator::getSignature(int x, int y)
{
    uint8_t signature = 0;

    for (int i = 0; i < 4; i++)
    {
        if (isInBounds(dirX[i] + x, dirY[i] + y))
            signature |= (int)walls[index(dirX[i] + x, dirY[i] + y)] << i;
        else 
            signature |= 1 << i;
        
        if (isInBounds(diagX[i] + x, diagY[i] + y))
            signature |= (int)walls[index(diagX[i] + x, diagY[i] + y)] << (i + 4);
        else 
            signature |= 1 << (i + 4);
    }

    return signature;
}

void MapGenerator::carveCoridor(sf::Vector2i start)
{
    int step = 0;
    int dir = rand() % 4; // Get a random cardinal direction

    do
    {   
        walls[index(start.x, start.y)] = false;

        if (!isCarvable(start.x + dirX[dir], start.y + dirY[dir]) || (rand() % 2 == 1 && step >= 2))
        {
            step = 0;
            std::vector<int> dirs;

            for (int i = 0; i < 4; i++)
            {
                if (isCarvable(start.x + dirX[i], start.y + dirY[i]))
                {
                    dirs.push_back(i);
                }
            }

            if (!dirs.empty())
            {
                int idx = rand() % dirs.size();
                dir = dirs[idx];
            }
            else
                dir = -1;
        }

        if (dir != -1)
        {
            start.x += dirX[dir];
            start.y += dirY[dir];
        }
        step++;

    } while (dir != -1);
}

void MapGenerator::fillAreas()
{
    int area = 0;

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (!walls[index(x, y)] && areas[index(x, y)] == -1)
            {
                floodFill(x, y, area);
                area ++;
            }
        }
    }
}

void MapGenerator::floodFill(int x, int y, int area)
{
    if (!isInBounds(x, y))
        return;

    if (walls[index(x, y)] || areas[index(x, y)] == area)
        return;

    areas[index(x, y)] = area;

    for (int i = 0; i < 4; i++)
    {
        floodFill(x + dirX[i], y + dirY[i], area);
    }
}

void MapGenerator::carveDoors()
{
    std::vector<sf::Vector2i> possibleDoors;

    do
    {
    possibleDoors.clear();
    
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (!walls[index(x, y)])
                continue;

            auto sig = getSignature(x, y);

            if (compSignatures(sig, 0b1111'0000, 0b1111'0101))
            {
                int a1 = areas[index(x - 1, y)];
                int a2 = areas[index(x + 1, y)];

                if (a1 != a2)
                {
                    // walls[index(x, y)] = false;
                    // floodFill(x, y, a1);
                    possibleDoors.push_back({x, y});
                }
            }
            else if (compSignatures(sig, 0b1111'0000, 0b1111'1010))
            {
                int a1 = areas[index(x, y - 1)];
                int a2 = areas[index(x, y + 1)];

                if (a1 != a2)
                {
                    // walls[index(x, y)] = false;
                    // floodFill(x, y, a1);
                    possibleDoors.push_back({x, y});

                }
            }
        }
    }

    if (!possibleDoors.empty())
    {
        auto idx = rand() % possibleDoors.size();
        auto tile = possibleDoors[idx];
        walls[index(tile.x, tile.y)] = false;
        floodFill(tile.x, tile.y, 99);
    }

    } while (!possibleDoors.empty());
}

std::stringstream MapGenerator::getMapAsStream()
{
    std::stringstream res;

    for (size_t i = 0; i < walls.size(); i++)
    {
        int tile = (walls[i]) ? 2 : 1;

        // @Debugging
        // int x = i % 16;
        // int y = i / 16;
        // tile = (isCarvable(x, y)) ? 11 : tile;

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

            if (!walls[index(room.pos.x + x, room.pos.y + y)])
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
            std::cout << walls[index(j, i)] << " ";
        }

        std::cout << '\n';
    }
}

void MapGenerator::printAreasArray()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            std::cout << std::setw(2) << areas[index(j, i)] << " ";
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
            std::cout << std::setw(3) << (int)getSignature(j, i) << " ";
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
    if (!isInBounds(x, y) || !walls[index(x, y)])
        return false;

    for (size_t i = 0; i < mask.size(); i++)
    {   
        auto sig = getSignature(x, y);

        if (compSignatures(sig, mask[i], match[i]))
            return true;
    }

    return false;
}

bool MapGenerator::compSignatures(uint8_t sig, uint8_t mask, uint8_t match)
{
    return ((sig | mask) == (match | mask));
}

bool MapGenerator::findFreeSpot(Room& room)
{
    int cnt = 0;
    while (!canPlaceRoom(room))
    {
        if (cnt == 100)
            return false;

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
            walls[index(room.pos.x + x, room.pos.y + y)] = false;
        }
    }
}

// void MapGenerator::updateSignature(int x, int y)
// {
//     for (int i = 0; i < 4; i++)
//     {
//         if (isInBounds(dirX[i] + x, dirY[i] + y))
//             walls[index(x, y)].signature |= (int)walls[index(dirX[i] + x, dirY[i] + y)].isWall << i;
//         else 
//             walls[index(x, y)].signature |= 1 << i;


//         if (isInBounds(diagX[i] + x, diagY[i] + y))
//             walls[index(x, y)].signature |= (int)walls[index(diagX[i] + x, diagY[i] + y)].isWall << (i + 4);
//         else 
//             walls[index(x, y)].signature |= 1 << (i + 4);
//     }
// }

// void MapGenerator::updateNeighbouringSignatures(int x, int y)
// {
//     for (int i = 0; i < 4; i++)
//     {
//         if (isInBounds(dirX[i] + x, dirY[i] + y))
//             updateSignature(dirX[i] + x, dirY[i] + y);
        
//         if (isInBounds(diagX[i] + x, diagY[i] + y))
//             updateSignature(diagX[i] + x, diagY[i] + y);
//     }
// }

void MapGenerator::shrinkRoom(Room& room)
{
    room.size.x = (room.size.x > 3) ? room.size.x - 1 : 3;
    room.size.y = (room.size.y > 3) ? room.size.y - 1 : 3;
}