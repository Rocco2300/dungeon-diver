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
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            std::cout << std::setw(2) << static_cast<int>(walls(x, y)) << " ";
        }

        std::cout << '\n';
    }
}

void MapGenerator::printAreasArray()
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            std::cout << std::setw(2) << areas(x, y) << " ";
        }

        std::cout << '\n';
    }
}

void MapGenerator::printSignatures()
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            std::cout << std::setw(3) << (int)getSignature(x, y) << " ";
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
            std::cout << roomMap(x, y) << " ";
        }

        std::cout << '\n';
    }
}

std::stringstream MapGenerator::getMapAsStream()
{
    std::stringstream res;

    for (size_t i = 0; i < walls.size(); i++)
    {
        // int tile;
        // if (walls[i] == 0) tile = 1;
        // else if (walls[i] == 1) tile = 2;
        // else tile = walls[i];

        // @Debugging
        // int x = i % 16;
        // int y = i / 16;
        // tile = (areas[index(x, y)] == -2) ? 12 : tile;

        res << static_cast<int>(walls[i]) << " ";
    }

    return res;
}

// Allocation
void MapGenerator::init()
{
    maxWidth = 8;
    maxHeight = 8;

    walls.alloc();
    std::fill(walls.begin(), walls.end(), WallTile::Wall);

    areas.alloc();
    std::fill(areas.begin(), areas.end(), -1);

    roomMap.alloc();
    std::fill(roomMap.begin(), roomMap.end(), 0);
}

void MapGenerator::clearMaps()
{
    std::fill(walls.begin(), walls.end(), WallTile::Wall);
    std::fill(areas.begin(), areas.end(), -1);
    std::fill(roomMap.begin(), roomMap.end(), 0);

    rooms.clear();
}

// Helpers
bool MapGenerator::isWall(int x, int y)
{
    if (!isInBounds(x, y))
        return true;

    return (walls(x, y) != WallTile::Empty && walls(x, y) != WallTile::None);
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
            signature |= isWall(dirX[i] + x, dirY[i] + y) << i;
        else 
            signature |= 1 << i;
        
        if (isInBounds(diagX[i] + x, diagY[i] + y))
            signature |= isWall(diagX[i] + x, diagY[i] + y) << (i + 4);
        else 
            signature |= 1 << (i + 4);
    }

    return signature;
}

Grid<int> MapGenerator::getColMap()
{
    Grid<int> ret;
    ret.alloc();

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            ret(x, y) = static_cast<int>(walls(x, y));
        }
    }

    return ret;
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
            roomMap(room.pos.x + x, room.pos.y + y) = rooms.size();
            walls(room.pos.x + x, room.pos.y + y) = WallTile::Empty;
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

            if (!isWall(room.pos.x + x, room.pos.y + y))
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
        auto flag = areas(pos.x, pos.y);

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
        walls(start.x, start.y) = WallTile::Empty;

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
        walls(deadEnds[i].x, deadEnds[i].y) = WallTile::Wall;
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
        if (isCarvable(pos.x + dirX[i], pos.y + dirY[i]) && 
            isWall(pos.x + dirX[i], pos.y + dirY[i]))
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
            if (isWall(x, y) && (getSignature(x, y) == 255))
            {
                result.push_back({x, y});
            }
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
            if (!isWall(x, y) && isCarvable(x, y))
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
            if (!isWall(x, y) && areas(x, y) == -1)
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
            walls(possibleDoors[idx].x, possibleDoors[idx].y) = WallTile::Door;
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

    if (isWall(x, y) || areas(x, y) == area)
        return;

    areas(x, y) = area;

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
    walls(tile.x, tile.y) = WallTile::Empty;

    // Merge two areas together
    int area{};
    if (isInBounds(tile.x + 1, tile.y) && areas(tile.x + 1, tile.y) != -1)
        area = areas(tile.x + 1, tile.y);
    else if (isInBounds(tile.x, tile.y + 1) && areas(tile.x, tile.y + 1) != 1)
        area = areas(tile.x, tile.y + 1);

    floodFill(tile.x, tile.y, area);
}

void MapGenerator::carveShortcut(const std::vector<sf::Vector2i>& possibleShortcuts)
{
    if (possibleShortcuts.empty())
        return;

    auto idx = rand() % possibleShortcuts.size();
    auto tile = possibleShortcuts[idx];
    walls(tile.x, tile.y) = WallTile::Empty;
}

int MapGenerator::getPathLength(int x, int y)
{
    sf::Vector2i a, b;
    auto colMap = getColMap();
    AStar aStar(colMap);
    Path path;

    if (isInBounds(x + 1, y) && areas(x + 1, y) != -1)
    {
        a = sf::Vector2i(x + 1, y);
        b = sf::Vector2i(x - 1, y);

        path = aStar.findPath(a, b);
    }
    else if (isInBounds(x, y + 1) && areas(x, y + 1) != -1)
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

        int a1 = (isInBounds(x - 1, y)) ? areas(x - 1, y) : -1;
        int a2 = (isInBounds(x + 1, y)) ? areas(x + 1, y) : -1;

        if (a1 != a2)
            return true;
    }
    else if (compSignatures(sig, 0b1111'0000, 0b1111'1010))
    {
        if (!sep)
            return true;
    
        int a1 = (isInBounds(x, y - 1)) ? areas(x, y - 1) : -1;
        int a2 = (isInBounds(x, y + 1)) ? areas(x, y + 1) : -1;

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
            if (!isWall(x, y))
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
            if (isWall(x, y))
                continue;

            if (!isValidDoor(x, y, false))
                continue;

            if (isInBounds(x + 1, y) && areas(x + 1, y) != -1)
            {
                if ((isInBounds(x + 1, y) && roomMap(x + 1, y) != 0) || 
                    (isInBounds(x - 1, y) && roomMap(x - 1, y) != 0))
                    res.push_back({x, y});
            }
            else if (isInBounds(x, y + 1) && areas(x, y + 1) != -1)
            {
                if ((isInBounds(x, y + 1) && roomMap(x, y + 1) != 0) || 
                    (isInBounds(x, y - 1) && roomMap(x, y - 1) != 0))
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

    walls(pos.x, pos.y) = WallTile::Entrance;
    entrance = pos;
}

void MapGenerator::placeExitStairs()
{
    auto distMap = getDistanceMap();

    int m = 0;
    sf::Vector2i pos;
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (distMap(x, y) > m)
            {
                m = distMap(x, y);
                pos = sf::Vector2i(x, y);
            }
        }
    }
    
    walls(pos.x, pos.y) = WallTile::Exit;
}

bool MapGenerator::isValidStairsPos(int x, int y)
{
    bool res = !isWall(x, y) && getSignature(x, y) != 0 && roomMap(x, y) != 0;

    for (int i = 0; i < 4; i++)
    {
        if (!isInBounds(x + dirX[i], y + dirY[i]))
            continue;

        if (walls(x + dirX[i], y + dirY[i]) == WallTile::Door)
            return false;

        if (!isInBounds(x + diagX[i], y + diagY[i]))
            continue;
        
        if (walls(x + diagX[i], y + diagY[i]) == WallTile::Door)
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
Grid<int> MapGenerator::getDistanceMap()
{
    Grid<int> res;
    res.alloc();
    std::fill(res.begin(), res.end(), 0);

    AStar aStar;
    auto colMap = getColMap();
    aStar.setColMap(colMap);

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (!isValidStairsPos(x, y))
                continue;

            auto dist = aStar.findPath(entrance, {x, y}).size();
            res(x, y) = dist;
        }
    }

    return res;
}