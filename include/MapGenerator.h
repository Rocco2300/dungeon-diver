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

    Cell() : isWall{true}, signature{255} { }
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

    std::stringstream getMapAsStream();
private:
    Room getRandomRoom();

    bool findFreeSpot(Room& room);
    bool canPlaceRoom(Room room);
    bool placeRoom(Room& room);
    bool isInBounds(int x, int y);

    int index(int x, int y);
    void carveOutRoom(Room room);
    void shrinkRoom(Room& room);
};

