#pragma once

#include <array>

#include <SFML/Graphics.hpp>

struct Room 
{
    sf::Vector2i pos;
    sf::Vector2i size;
};

class MapGenerator
{
private:
    std::array<int, 16*16> walls;
public:
    MapGenerator();

    void generateRooms();
    Room getRandomRoom();
    bool canPlaceRoom(Room room);
    bool placeRoom(Room room);

    void printWallsArray();
private:
    int index(int x, int y);
    bool isInBounds(int x, int y);
    bool findFreeSpot(Room& room);
    void carveOutRoom(Room room);
};

