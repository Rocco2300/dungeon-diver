#include "MapGenerator.h"

#include <iostream>
#include <iomanip>
#include <random>

#include "Constants.h"

// Publics
MapGenerator::MapGenerator()
{
    walls.resize(16*16);

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            walls[index(x, y)] = 1;
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
    carveShortcuts();
    fillDeadEnds();
}

void MapGenerator::printWallsArray()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            std::cout << std::setw(2) << walls[index(j, i)] << " ";
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

std::stringstream MapGenerator::getMapAsStream()
{
    std::stringstream res;

    for (size_t i = 0; i < walls.size(); i++)
    {
        int tile;
        if (walls[i] == 0) tile = 1;
        else if (walls[i] == 1) tile = 2;
        else tile = walls[i];

        // @Debugging
        // int x = i % 16;
        // int y = i / 16;
        // tile = (areas[index(x, y)] == -2) ? 10 : tile;

        res << tile << " ";
    }

    return res;
}

// Helpers
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
    if (!isInBounds(x, y))
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

// Room Generation
void MapGenerator::generateRooms()
{
    for (int i = 0; i < 4; i++)
    {
        auto room = getRandomRoom();
        placeRoom(room);
    }

    // updateMapSignatures();
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

void MapGenerator::shrinkRoom(Room& room)
{
    room.size.x = (room.size.x > 3) ? room.size.x - 1 : 3;
    room.size.y = (room.size.y > 3) ? room.size.y - 1 : 3;
}

Room MapGenerator::getRandomRoom()
{
    Room res;

    sf::Vector2i size;

    // 3 - 8
    size.x = rand() % 6 + 3;
    size.y = rand() % 6 + 3;

    res.size = size;

    return res;
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

// Maze Generation
void MapGenerator::carveMaze()
{
    std::vector<sf::Vector2i> starts;

    do 
    {
        starts.clear();

        starts = findPossibleStarts();

        if (!starts.empty())
        {
            int idx = rand() % starts.size();

            carveCoridor(starts[idx]);
        }

    } while (!starts.empty());
}

void MapGenerator::fillDeadEnds()
{
    std::vector<sf::Vector2i> deadEnds;

    do
    {   
        deadEnds.clear();

        deadEnds = findDeadEnds();

        fillInWalls(deadEnds);

    } while (!deadEnds.empty());
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
            std::vector<int> dirs = getCarvableDirs(start);
            dir = getRandomDirection(dirs);
        }

        if (dir != -1)
        {
            start.x += dirX[dir];
            start.y += dirY[dir];
        }
        step++;

    } while (dir != -1);
}

void MapGenerator::fillInWalls(std::vector<sf::Vector2i> deadEnds)
{
    for (int i = 0; i < deadEnds.size(); i++)
    {
        walls[index(deadEnds[i].x, deadEnds[i].y)] = 1;
    }
}

int MapGenerator::getRandomDirection(std::vector<int> dirs)
{   
    int dir;

    if (!dirs.empty())
    {
        int idx = rand() % dirs.size();
        dir = dirs[idx];
    }
    else
        dir = -1;
    
    return dir;
}

std::vector<int> MapGenerator::getCarvableDirs(sf::Vector2i pos)
{
    std::vector<int> result;

    for (int i = 0; i < 4; i++)
    {
        int idx = index(pos.x + dirX[i], pos.y + dirY[i]);
        if (isCarvable(pos.x + dirX[i], pos.y + dirY[i]) && walls[idx])
        {
            result.push_back(i);
        }
    }

    return result;
}

std::vector<sf::Vector2i> MapGenerator::findPossibleStarts()
{
    std::vector<sf::Vector2i> result;

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (walls[index(x, y)] && getSignature(x, y) == 255)
                result.push_back({x, y});
        }
    }

    return result;
}

std::vector<sf::Vector2i> MapGenerator::findDeadEnds()
{
    std::vector<sf::Vector2i> result;

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (!walls[index(x, y)] && isCarvable(x, y))
                result.push_back({x, y});
        }
    }

    return result;
}

// Door Generation
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

void MapGenerator::carveDoors()
{
    std::vector<sf::Vector2i> possibleDoors;

    do
    {
        possibleDoors.clear();
        
        possibleDoors = getPossibleDoors();

        carveDoor(possibleDoors);

    } while (!possibleDoors.empty());
}

void MapGenerator::carveShortcuts()
{
    std::vector<sf::Vector2i> possibleShortcuts;

    do
    {
        possibleShortcuts.clear();

        possibleShortcuts = getPossibleShortcuts();

        carveShortcut(possibleShortcuts);

    } while (!possibleShortcuts.empty());
    
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

void MapGenerator::carveDoor(std::vector<sf::Vector2i> possibleDoors)
{
    if (possibleDoors.empty())
        return;

    auto idx = rand() % possibleDoors.size();
    auto tile = possibleDoors[idx];
    walls[index(tile.x, tile.y)] = false;

    // Merge two areas together
    int area{};
    if (areas[index(tile.x + 1, tile.y)] != -1)
        area = areas[index(tile.x + 1, tile.y)];
    else if (areas[index(tile.x, tile.y + 1)] != 1)
        area = areas[index(tile.x, tile.y + 1)];

    floodFill(tile.x, tile.y, area);
}

void MapGenerator::carveShortcut(std::vector<sf::Vector2i> possibleShortcuts)
{
    if (possibleShortcuts.empty())
        return;

    auto idx = rand() % possibleShortcuts.size();
    auto tile = possibleShortcuts[idx];
    // areas[index(tile.x, tile.y)] = -2;
    walls[index(tile.x, tile.y)] = false;
}

int MapGenerator::getPathLength(int x, int y)
{
    sf::Vector2i a, b;
    AStar aStar(walls);
    Path path;

    if (areas[index(x + 1, y)] != -1)
    {
        a = sf::Vector2i(x + 1, y);
        b = sf::Vector2i(x - 1, y);

        path = aStar.findPath(a, b);
    }
    else if (areas[index(x, y + 1)] != -1)
    {
        a = sf::Vector2i(x, y + 1);
        b = sf::Vector2i(x, y - 1);

        path = aStar.findPath(a, b);
    }

    return path.size();
}

bool MapGenerator::isValidDoor(int x, int y, bool sep)
{
    auto sig = getSignature(x, y);

    if (compSignatures(sig, 0b1111'0000, 0b1111'0101))
    {
        if (!sep)
            return true;

        int a1 = areas[index(x - 1, y)];
        int a2 = areas[index(x + 1, y)];

        if (a1 != a2)
            return true;
    }
    else if (compSignatures(sig, 0b1111'0000, 0b1111'1010))
    {
        if (!sep)
            return true;
    
        int a1 = areas[index(x, y - 1)];
        int a2 = areas[index(x, y + 1)];

        if (a1 != a2)
            return true;
    }

    return false;
}

std::vector<sf::Vector2i> MapGenerator::getPossibleDoors()
{
    std::vector<sf::Vector2i> result;

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (!walls[index(x, y)])
                continue;

            if (isValidDoor(x, y, true))
                result.push_back({x, y});
        }
    }

    return result;
}

std::vector<sf::Vector2i> MapGenerator::getPossibleShortcuts()
{
    std::vector<sf::Vector2i> result;

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (!isValidDoor(x, y, false))
                continue;

            auto dist = getPathLength(x, y);

            if (dist >= 20)
                result.push_back({x, y});
        }
    }

    return result;
}
