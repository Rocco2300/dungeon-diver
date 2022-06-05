#pragma once

#include <array>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Tile.h"

#include <cstdint>

struct Cell
{
    bool isWall;
    uint8_t signature;

    Cell() : isWall{true}, signature{0} { }
};

struct Room 
{
    sf::Vector2i pos;
    sf::Vector2i size;
};

class MapGenerator
{
private:
    std::array<Cell, 16*16> walls;
public:
    MapGenerator();

    void generateRooms();
    void printWallsArray();
    void printSignatures();

    std::stringstream getMapAsStream();
private:
    Room getRandomRoom();

    bool findFreeSpot(Room& room);
    bool canPlaceRoom(Room room);
    bool placeRoom(Room& room);
    bool isInBounds(int x, int y);

    int index(int x, int y);
    void carveOutRoom(Room room);
    void updateSignature(int x, int y);
    void updateNeighbouringSignatures(int x, int y);
    void shrinkRoom(Room& room);
};
