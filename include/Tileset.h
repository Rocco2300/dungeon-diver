#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "ResourceHolder.h"

class Tileset : public sf::Drawable
{
private:
    sf::Vector2i tileSize;

    sf::Texture texture;
    sf::VertexArray quad;
public:
    Tileset();
    Tileset(const char* path, sf::Vector2i tileSize);
    void create(const char* path, sf::Vector2i tileSize);

    void setSpriteIndex(int index);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
