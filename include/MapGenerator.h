#pragma once

#include <array>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "AStar.h"

#include <cstdint>

// struct Cell
// {
//     bool isWall;
//     uint8_t signature;

//     Cell() : isWall{true}, signature{0} { }
// };

struct Room 
{
    sf::Vector2i pos;
    sf::Vector2i size;
};

class MapGenerator
{
private:
    std::array<uint8_t, 5> mask  = {0         , 0b00110000, 0b01100000, 0b11000000, 0b10010000};
    std::array<uint8_t, 5> match = {0b11111111, 0b11111110, 0b11111101, 0b11111011, 0b11110111};

    std::vector<int>  areas;
    std::vector<int>  walls;
    std::vector<int>  roomMap;
    std::vector<Room> rooms; 
public:
    MapGenerator();

    void generateMap();
    void printWallsArray();
    void printAreasArray();
    void printSignatures();
    void printRoomMap();

    std::stringstream getMapAsStream();
private:
    // Helpers
    int     index(int x, int y);
    bool    isInBounds(int x, int y);
    bool    isCarvable(int x, int y);
    bool    compSignatures(uint8_t sig, uint8_t mask, uint8_t match);
    uint8_t getSignature(int x, int y);

    // Room Generation
    void generateRooms();
    void carveOutRoom(Room room);
    void shrinkRoom(Room& room);

    Room getRandomRoom();
    bool findFreeSpot(Room& room);
    bool canPlaceRoom(Room room);
    bool placeRoom(Room& room);
    
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
    void carveDoors();
    void carveShortcuts();
    void floodFill(int x, int y, int area);
    void carveDoor(const std::vector<sf::Vector2i>& possibleDoors);
    void carveShortcut(const std::vector<sf::Vector2i>& possibleShortcuts);

    int                       getPathLength(int x, int y);
    bool                      isValidDoor(int x, int y, bool sep);
    std::vector<sf::Vector2i> getPossibleDoors();
    std::vector<sf::Vector2i> getPossibleShortcuts();
};

