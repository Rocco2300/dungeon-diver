#include "Map.h"

#include <iostream>
#include <algorithm>
#include <fstream>

Map::Map()
{
    tiles.alloc();
}

Tile& Map::at(int x, int y)
{
    return *tiles(x, y);
}

Tile& Map::at(sf::Vector2i pos)
{
    return *tiles(pos.x, pos.y);
}

Tile& Map::operator()(int x, int y)
{
    return *tiles(x, y);
}

Tile& Map::operator()(sf::Vector2i pos)
{
    return *tiles(pos.x, pos.y);
}

void Map::setSize(sf::Vector2i size)
{
    this->size = size;
}

void Map::setTileset(Tileset& tileset)
{
    this->tileset = &tileset;
}

void Map::loadMap(const char* path)
{
    std::ifstream in(path);

    _loadMap(in);

    in.close();
}

void Map::loadMap(std::istream& in)
{
    _loadMap(in);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i = 0; i < tiles.size(); i++)
    {
        int x = i % 16;
        int y = i / 16;

        sf::Transform transform;
        transform.translate(x * 8, y * 8);
        sf::RenderStates states;
        states.transform = transform;

        target.draw(*tiles[i].get(), states);
    }

}

void Map::_loadMap(std::istream& in)
{
    // tiles.clear();
    tiles.dealloc();
    tiles.alloc();

    int id;
    for (int i = 0; i < 16; i++)
    {
        std::vector<int> temp;
        for (int j = 0; j < 16; j++)
        {
            in >> id;

            std::unique_ptr<Tile> tile;
            if (id == 7 || id == 8)
                tile = std::make_unique<PotTile>();
            else if (id == 3 || id == 5)
                tile = std::make_unique<ChestTile>();
            else if (id == 10)
                tile = std::make_unique<ExitStairsTile>();
            else if (id == 11)
                tile = std::make_unique<DoorTile>();
            else
                tile = std::make_unique<Tile>();
            
            tile->setTileset(*tileset);
            tile->setID(id);

            if (std::find(walkableTiles.begin(), walkableTiles.end(), id) != walkableTiles.end())
                tile->setWalkable(true);
            else 
                tile->setWalkable(false);

            tiles(j, i) = std::move(tile);
        }
    }
}