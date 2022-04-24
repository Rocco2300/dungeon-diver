#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class Tileset : public sf::Drawable
{
private:
    int tileWidth;
    int tileHeight;

    std::unique_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> sprite;
public:
    Tileset();
    Tileset(const char* path, int tileWidth, int tileHeight);
    Tileset(Tileset&& other);
    Tileset& operator=(const Tileset& other);

    void setSpriteIndex(int index);
    void setPosition(int x, int y);
    void setOrigin(int x, int y);
    void setScale(float x, float y);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
