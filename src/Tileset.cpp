#include "Tileset.h"

#include <iostream>

Tileset::Tileset()
{

}

Tileset::Tileset(const char* path, int tileWidth, int tileHeight)
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    if (!texture->loadFromFile(path))
        std::cerr << "Error loading tileset texture!\n";

    sprite->setTexture(*texture);
    sprite->setTextureRect({{0, 0}, {tileWidth, tileHeight}});
}

Tileset::Tileset(Tileset&& other)
{
    tileWidth = other.tileWidth;
    tileHeight = other.tileHeight;

    texture = std::move(other.texture);
    sprite = std::move(other.sprite);
}


Tileset& Tileset::operator=(const Tileset& other)
{
    this->tileWidth = other.tileWidth;
    this->tileHeight = other.tileHeight;

    auto img = other.texture->copyToImage();

    if (!texture->loadFromImage(img))
        std::cerr << "Error loading tileset texture!\n";

    sprite->setTexture(*texture);
    sprite->setTextureRect({{0, 0}, {tileWidth, tileHeight}});

    return *this;
}

void Tileset::setSpriteIndex(int index)
{
    int width = texture->getSize().x;
    int x = index % width;
    int y = index / width;
    sprite->setTextureRect({{x * tileWidth, y * tileHeight}, {tileWidth, tileHeight}});
}

void Tileset::setPosition(int x, int y)
{
    sprite->setPosition(x, y);
}

void Tileset::setOrigin(int x, int y)
{
    sprite->setOrigin(x, y);
}

void Tileset::setScale(float x, float y)
{
    sprite->setScale(x, y);
}

void Tileset::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*sprite, states);
}