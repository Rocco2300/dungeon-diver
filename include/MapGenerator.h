#pragma once

#include <array>

#include <SFML/Graphics.hpp>

class MapGenerator
{
private:
    std::array<int, 16*16> walls;
public:
    MapGenerator();

    sf::Vector2i getRandomRoom();
    bool placeRoom(sf::Vector2i room);
private:
    int index(int x, int y);
};

