#include "Map.h"

#include <iostream>
#include <algorithm>
#include <fstream>

Map::Map()
{
}

Tile& Map::operator()(int x, int y)
{
    auto idx = y * size.x + x;
    return *tiles[idx].get();
}

Tile& Map::operator()(sf::Vector2i pos)
{
    auto idx = pos.y * size.x + pos.x;
    return *tiles[idx].get();
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

    int x;
    for (int i = 0; i < 16; i++)
    {
        std::vector<int> temp;
        for (int j = 0; j < 16; j++)
        {
            in >> x;

            std::unique_ptr<Tile> tile;
            if (x == 7 || x == 8)
                tile = std::make_unique<PotTile>();
            else if (x == 3 || x == 5)
                tile = std::make_unique<ChestTile>();
            else
                tile = std::make_unique<Tile>();
            
            tile->setTileset(*tileset);
            tile->setID(x);

            if (std::find(walkableTiles.begin(), walkableTiles.end(), x) != walkableTiles.end())
            {
                if (x == 10) std::cout << "muie\n";

                tile->setWalkable(true);
            }
            else 
            {
                tile->setWalkable(false);
            }

            tiles.push_back(std::move(tile));
        }
    }

    in.close();
}

void Map::loadMap(std::istream& in)
{
    int x;
    for (int i = 0; i < 16; i++)
    {
        std::vector<int> temp;
        for (int j = 0; j < 16; j++)
        {
            in >> x;

            std::unique_ptr<Tile> tile;
            if (x == 7 || x == 8)
                tile = std::make_unique<PotTile>();
            else if (x == 3 || x == 5)
                tile = std::make_unique<ChestTile>();
            else
                tile = std::make_unique<Tile>();
            
            tile->setTileset(*tileset);
            tile->setID(x);

            if (std::find(walkableTiles.begin(), walkableTiles.end(), x) != walkableTiles.end())
                tile->setWalkable(true);
            else 
                tile->setWalkable(false);

            tiles.push_back(std::move(tile));
        }
    }
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