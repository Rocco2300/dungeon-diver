#pragma once

#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "AStar.h"
#include "Grid.h"

#include <cstdint>

struct Room 
{
    sf::Vector2i pos;
    sf::Vector2i size;
};

class MapGenerator
{
private:
    // Max room size
    int maxWidth;
    int maxHeight;
    sf::Vector2i entrance;

    std::array<uint8_t, 5> mask  = {0         , 0b00110000, 0b01100000, 0b11000000, 0b10010000};
    std::array<uint8_t, 5> match = {0b11111111, 0b11111110, 0b11111101, 0b11111011, 0b11110111};

    Grid<int>  areas;
    Grid<int>  walls;
    Grid<int>  roomMap;
    std::vector<Room> rooms; 
public:
    MapGenerator() = default;

    sf::Vector2i getEntrance();

    void generateMap();
    void printWallsArray();
    void printAreasArray();
    void printSignatures();
    void printRoomMap();

    std::stringstream getMapAsStream();
private:
    // Allocation
    void init();
    void clearMaps();

    // Helpers
    bool    isInBounds(int x, int y);
    bool    isCarvable(int x, int y);
    bool    compSignatures(uint8_t sig, uint8_t mask, uint8_t match);
    uint8_t getSignature(int x, int y);

    // Room Generation
    void generateRooms();
    void carveOutRoom(Room room);
    void solveIsolatedRooms();

    bool findFreeSpot(Room& room);
    bool canPlaceRoom(Room room);
    bool placeRoom(Room& room);
    bool hasIsolatedRoom();
    Room getRandomRoom();
    
    // Maze Generation
    void carveMaze();
    void fillDeadEnds();
    void carveCoridor(sf::Vector2i start);
    void fillInWalls(const std::vector<sf::Vector2i>& deadEnds);

    int                       getRandomDirection(std::vector<int> dirs);
    std::vector<int>          getCarvableDirs(sf::Vector2i pos);
    std::vector<sf::Vector2i> findPossibleStarts();
    std::vector<sf::Vector2i> findDeadEnds();

    // Door Generation
    void fillAreas();
    void placeDoors();
    void carveDoors();
    void carveShortcuts();
    void floodFill(int x, int y, int area);
    void carveDoor(const std::vector<sf::Vector2i>& possibleDoors);
    void carveShortcut(const std::vector<sf::Vector2i>& possibleShortcuts);

    int                       getPathLength(int x, int y);
    bool                      isValidDoor(int x, int y, bool sep);
    std::vector<sf::Vector2i> getPossibleDoorways();
    std::vector<sf::Vector2i> getPossibleShortcuts();
    std::vector<sf::Vector2i> getPossibleDoors();

    void placeStairs();
    void placeEntranceStairs();
    void placeExitStairs();

    bool isValidStairsPos(int x, int y);
    Grid<int> getDistanceMap();
    std::vector<sf::Vector2i> getPossibleEntrances();
};

