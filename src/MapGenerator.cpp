#include "MapGenerator.h"

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <random>
#include <map>
#include <chrono>

#include "Constants.h"

sf::Vector2i MapGenerator::getEntrance()
{
    return entrance;
}

void MapGenerator::generateMap()
{   
    init();

    generateRooms();
    carveMaze();
    fillAreas();
    carveDoors();
    solveIsolatedRooms();
    carveShortcuts();
    fillDeadEnds();
    placeDoors();
    placeStairs();
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

void MapGenerator::printRoomMap()
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            std::cout << roomMap[index(x, y)] << " ";
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
        // tile = (areas[index(x, y)] == -2) ? 12 : tile;

        res << tile << " ";
    }

    return res;
}

// Allocation
void MapGenerator::init()
{
    maxWidth = 8;
    maxHeight = 8;

    walls.alloc();
    std::fill(walls.begin(), walls.end(), 1);

    areas.alloc();
    std::fill(areas.begin(), areas.end(), -1);

    roomMap.alloc();
    std::fill(roomMap.begin(), roomMap.end(), 0);
}

void MapGenerator::clearMaps()
{
    std::fill(walls.begin(), walls.end(), 1);
    std::fill(areas.begin(), areas.end(), -1);
    std::fill(roomMap.begin(), roomMap.end(), 0);

    rooms.clear();
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
    rooms.push_back(room);

    for (int y = 0; y < room.size.y; y++)
    {
        for (int x = 0; x < room.size.x; x++)
        {
            roomMap[index(room.pos.x + x, room.pos.y + y)] = rooms.size();
            walls[index(room.pos.x + x, room.pos.y + y)] = false;
        }
    }
}

void MapGenerator::solveIsolatedRooms()
{
    // The case is so rare recursive
    // shouldn't overflow
    if (hasIsolatedRoom())
    {
        clearMaps();
        init();

        generateRooms();
        carveMaze();
        fillAreas();
        carveDoors();

        solveIsolatedRooms();
    }
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

        maxWidth--;
        maxHeight--;
        room = getRandomRoom();
        cnt ++;
    }

    carveOutRoom(room);

    return true;
}

bool MapGenerator::hasIsolatedRoom()
{
    // We have to find if there is a room with a different area flag
    // Map to hold number of rooms with a certain area flag
    std::map<int, int> zoneRoomMap;

    for (size_t i = 0; i < rooms.size(); i++)
    {
        auto pos = rooms[i].pos;
        auto flag = areas[index(pos.x, pos.y)];

        zoneRoomMap[flag]++;
    }

    // If there is more than one flag on the map
    // one room hasn't been expanded, thus is isolated
    if (zoneRoomMap.size() != 1)
        return true;

    return false;
}

Room MapGenerator::getRandomRoom()
{
    Room res;

    // Clamp values so we don't divide by 0
    maxWidth  = (maxWidth >= 3) ? maxWidth : 3;
    maxHeight = (maxHeight >= 3) ? maxHeight : 3;

    res.size.x = rand() % (maxWidth  - 2) + 3;
    res.size.y = rand() % (maxHeight - 2) + 3;

    return res;
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

void MapGenerator::fillInWalls(const std::vector<sf::Vector2i>& deadEnds)
{
    for (size_t i = 0; i < deadEnds.size(); i++)
    {
        walls[index(deadEnds[i].x, deadEnds[i].y)] = 1;
        // areas[index(deadEnds[i].x, deadEnds[i].y)] = -2;
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

void MapGenerator::placeDoors()
{
    std::vector<sf::Vector2i> possibleDoors;

    do
    {
        possibleDoors.clear();

        possibleDoors = getPossibleDoors();

        if (possibleDoors.size() > 0)
        {
            auto idx = rand() % possibleDoors.size();
            walls[index(possibleDoors[idx].x, possibleDoors[idx].y)] = 11;
        }

    } while (!possibleDoors.empty());
    
}

void MapGenerator::carveDoors()
{
    std::vector<sf::Vector2i> possibleDoors;

    do
    {
        possibleDoors.clear();
        
        possibleDoors = getPossibleDoorways();

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

void MapGenerator::carveDoor(const std::vector<sf::Vector2i>& possibleDoors)
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

void MapGenerator::carveShortcut(const std::vector<sf::Vector2i>& possibleShortcuts)
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

std::vector<sf::Vector2i> MapGenerator::getPossibleDoorways()
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

std::vector<sf::Vector2i> MapGenerator::getPossibleDoors()
{
    std::vector<sf::Vector2i> res;
    
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (walls[index(x, y)])
                continue;

            if (!isValidDoor(x, y, false))
                continue;

            if (isInBounds(x + 1, y) && areas[index(x + 1, y)] != -1)
            {
                if (roomMap[index(x + 1, y)] != 0 || roomMap[index(x - 1, y)] != 0)
                    res.push_back({x, y});
            }
            else if (isInBounds(x, y + 1) && areas[index(x, y + 1)] != -1)
            {
                if (roomMap[index(x, y + 1)] != 0 || roomMap[index(x, y - 1)] != 0)
                    res.push_back({x, y});
            }
        }
    }

    return res;
}

void MapGenerator::placeStairs()
{
    placeEntranceStairs();
    placeExitStairs();
}

void MapGenerator::placeEntranceStairs()
{
    auto possibleEntrances = getPossibleEntrances();

    auto idx = rand() % possibleEntrances.size();
    auto pos = possibleEntrances[idx];

    walls[index(pos.x, pos.y)] = 9;
    entrance = pos;
}

void MapGenerator::placeExitStairs()
{
    auto distMap = getDistanceMap();

    int m = 0;
    sf::Vector2i pos;
    for (size_t i = 0; i < distMap.size(); i++)
    {
        if (distMap[i] > m)
        {
            m = distMap[i];
            pos = sf::Vector2i(i % 16, i / 16);
        }
    }

    walls[index(pos.x, pos.y)] = 10;
}

bool MapGenerator::isValidStairsPos(int x, int y)
{
    bool res = walls[index(x, y)] == 0 && getSignature(x, y) != 0 && roomMap[index(x, y)] != 0;

    for (int i = 0; i < 4; i++)
    {
        if (!isInBounds(x + dirX[i], y + dirY[i]))
            continue;

        if (walls[index(x + dirX[i], y + dirY[i])] == 11)
            return false;

        if (!isInBounds(x + diagX[i], y + diagY[i]))
            continue;
        
        if (walls[index(x + diagX[i], y + diagY[i])] == 11)
            return false;
    }

    return res;
}

std::vector<sf::Vector2i> MapGenerator::getPossibleEntrances()
{
    std::vector<sf::Vector2i> res;

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (isValidStairsPos(x, y))
                res.push_back({x, y});
        }
    }

    return res;
}

// Get distance map to valid stairs tiles
std::vector<int> MapGenerator::getDistanceMap()
{
    std::vector<int> res;
    res.resize(16 * 16);

    AStar aStar;
    aStar.setColMap(walls);

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (!isValidStairsPos(x, y))
                continue;

            auto dist = aStar.findPath(entrance, {x, y}).size();
            res[index(x, y)] = dist;
        }
    }

    return res;
}