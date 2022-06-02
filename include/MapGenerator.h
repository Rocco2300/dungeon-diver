#pragma once

#include <array>

class MapGenerator
{
private:
    std::array<int, 16*16> walls;
public:
    MapGenerator() = default;
};

