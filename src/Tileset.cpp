#include "Tileset.h"

#include <iostream>

Tileset::Tileset()
{

}

Tileset::Tileset(const char* path, sf::Vector2i tileSize)
{
    this->tileSize = tileSize;

    if (!texture.loadFromFile(path))
        std::cerr << "Error!\n";
    
    quad.setPrimitiveType(sf::Quads);
    quad.resize(4);

    quad[0].position = sf::Vector2f(0.f, 0.f);
    quad[1].position = sf::Vector2f(tileSize.x, 0.f);
    quad[2].position = sf::Vector2f(tileSize.x, tileSize.y);
    quad[3].position = sf::Vector2f(0.f, tileSize.y);

    quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    quad[1].texCoords = sf::Vector2f(tileSize.x, 0.f);
    quad[2].texCoords = sf::Vector2f(tileSize.x, tileSize.y);
    quad[3].texCoords = sf::Vector2f(0.f, tileSize.y);
}

void Tileset::create(const char* path, sf::Vector2i tileSize)
{
    this->tileSize = tileSize;

    if (!texture.loadFromFile(path))
        std::cerr << "Error!\n";
    
    quad.setPrimitiveType(sf::Quads);
    quad.resize(4);

    quad[0].position = sf::Vector2f(0.f, 0.f);
    quad[1].position = sf::Vector2f(tileSize.x, 0.f);
    quad[2].position = sf::Vector2f(tileSize.x, tileSize.y);
    quad[3].position = sf::Vector2f(0.f, tileSize.y);

    quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    quad[1].texCoords = sf::Vector2f(tileSize.x, 0.f);
    quad[2].texCoords = sf::Vector2f(tileSize.x, tileSize.y);
    quad[3].texCoords = sf::Vector2f(0.f, tileSize.y);
}

void Tileset::setSpriteIndex(int index)
{
    int width = texture.getSize().x / tileSize.x;
    int x = index % width;
    int y = index / width;
    // sprite->setTextureRect({{x * tileWidth, y * tileHeight}, {tileWidth, tileHeight}});

    quad[0].texCoords = sf::Vector2f(0.f + x * tileSize.x, 0.f + y * tileSize.y);
    quad[1].texCoords = sf::Vector2f((x + 1) * tileSize.x, 0.f + y * tileSize.y);
    quad[2].texCoords = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
    quad[3].texCoords = sf::Vector2f(0.f + x * tileSize.x, (y + 1) * tileSize.y);
}

void Tileset::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &texture;

    target.draw(quad, states);
}