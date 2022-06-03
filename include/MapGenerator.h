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
    void printWallsArray();
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

