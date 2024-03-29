#pragma once

#include "InteractableTile.h"
#include "Grid.h"

#include <memory>
#include <array>

class Map : public sf::Drawable
{
private:
    const std::array<int, 4> walkableTiles = {0, 1, 9, 10};
    // const int walkableTiles[4] = {0, 1, 9, 10};

    sf::Vector2i size;

    Tileset* tileset;

    Grid<std::unique_ptr<Tile>> tiles;
public:
    Map();
//    void create(sf::Vector2i size);

    Tile& at(int x, int y);
    Tile& at(sf::Vector2i pos);

    Tile& operator()(int x, int y);
    Tile& operator()(sf::Vector2i pos);

    void setSize(sf::Vector2i size);
    void setTileset(Tileset& tileset);
    void loadMap(const char* path);
    void loadMap(std::istream& in);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    void loadMapImpl(std::istream& in);
};
