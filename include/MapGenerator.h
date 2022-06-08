#pragma once

#include <array>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Tile.h"

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
    std::vector<bool> walls;
public:
    MapGenerator();

    void generateMap();
    void printWallsArray();
    void printAreasArray();
    void printSignatures();

    std::stringstream getMapAsStream();
private:
    int     index(int x, int y);
    bool    isInBounds(int x, int y);
    bool    isCarvable(int x, int y);
    bool    compSignatures(uint8_t sig, uint8_t mask, uint8_t match);
    Room    getRandomRoom();
    uint8_t getSignature(int x, int y);

    // Room Generation
    void generateRooms();
    void carveOutRoom(Room room);
    void shrinkRoom(Room& room);

    bool findFreeSpot(Room& room);
    bool canPlaceRoom(Room room);
    bool placeRoom(Room& room);
    
    
    // void updateMapSignatures();
    // void updateSignature(int x, int y);
    // void updateNeighbouringSignatures(int x, int y);
    // Maze Generation
    void carveMaze();
    void carveCoridor(sf::Vector2i start);

    // Break out doors
    void fillAreas();
    void floodFill(int x, int y, int area);
    void carveDoors();
    void carveDoor(std::vector<sf::Vector2i> possibleDoors);
    bool isValidDoor(int x, int y);
    std::vector<sf::Vector2i> getPossibleDoors();
};

