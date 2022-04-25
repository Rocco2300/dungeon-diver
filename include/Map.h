#pragma once

#include "Tile.h"

class Map : public sf::Drawable
{
private:
    const int interactableTiles[4] = {3, 5, 7, 8};
    const int walkableTiles[2] = {0, 1};

    sf::Vector2i size;

    Tileset* tileset;

    std::vector<Tile> tiles;
public:
    Map();
    void create(sf::Vector2i size);

    Tile& operator()(int x, int y);
    Tile& operator()(sf::Vector2i pos);

    void setSize(sf::Vector2i size);
    void setTileset(Tileset& tileset);
    void loadMap(const char* path);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
