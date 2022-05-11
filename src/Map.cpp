#include "Map.h"

#include <algorithm>
#include <fstream>

Map::Map()
{
}

Tile& Map::operator()(int x, int y)
{
    auto idx = y * size.x + x;
    return *tiles[idx];
}

Tile& Map::operator()(sf::Vector2i pos)
{
    auto idx = pos.y * size.x + pos.x;
    return *tiles[idx];
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

            Tile* tile;
            if (x == 7 || x == 8)
                tile = new PotTile();
            else if (x == 3 || x == 5)
                tile = new ChestTile();
            else
                tile = new Tile();
            
            tile->setTileset(*tileset);
            tile->setID(x);

            if (std::find(walkableTiles, walkableTiles+2, x) != walkableTiles+2)
                tile->setWalkable(true);
            else 
                tile->setWalkable(false);
            
            // if (x == 2)
            //     tile->setTileType(TileType::Wall);
            // else if (x == 3)
            //     tile->setTileType(TileType::LargeChest);
            // else if (x == 5)
            //     tile->setTileType(TileType::SmallChest);
            // else 
            //     tile->setTileType(TileType::Deco);

            tiles.push_back(tile);
        }
    }

    in.close();
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

        target.draw(*tiles[i], states);
    }

}