#include "Text.h"

Text::Text() : width(3), height(5), letterSpacing(1), text("")
{
}

Text::Text(sf::Texture& texture, int width, int height, std::string str) 
    : texture(&texture), width(width), height(height), letterSpacing(1), text(str)
{
    setString(str);
}

void Text::setSpacing(int spacing)
{
    letterSpacing = spacing;
}

void Text::setString(std::string str)
{
    size.x = str.length() * width + str.length() * letterSpacing - letterSpacing;
    size.y = height;

    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(str.length() * 4);

    for (size_t i = 0; i < str.length(); i++)
    {
        auto t = getTextureIndex(str[i]);
        auto* quad = &vertices[i * 4];

        quad[0].position = sf::Vector2f(i * width + i * letterSpacing, 0);
        quad[1].position = sf::Vector2f((i + 1) * width + i * letterSpacing, 0);
        quad[2].position = sf::Vector2f((i + 1) * width + i * letterSpacing, height);
        quad[3].position = sf::Vector2f(i * width + i * letterSpacing, height);

        quad[0].texCoords = sf::Vector2f(t.x * width, t.y * height);
        quad[1].texCoords = sf::Vector2f((t.x + 1) * width, t.y * height);
        quad[2].texCoords = sf::Vector2f((t.x + 1) * width, (t.y + 1) * height);
        quad[3].texCoords = sf::Vector2f(t.x * width, (t.y + 1) * height);
    }
}

void Text::setTexture(sf::Texture& texture)
{
    this->texture = &texture;
}

void Text::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
}

void Text::setCharacterSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform translate;
    translate.translate(pos);

    states.texture = texture;
    states.transform *= translate;

    target.draw(vertices, states);
}

sf::Vector2i Text::getTextureIndex(char c)
{
    sf::Vector2i res;

    if (c == ' ')
    {
        res.x = 25;
        res.y = 2;
    }
    if (c >= 97 && c <= 122)
    {
        res.x = c - 97;
        res.y = 0;
    }
    else if (c >= 65 && c <= 90)
    {
        res.x = c - 65;
        res.y = 1;
    }
    else if (c >= 48 && c <= 57)
    {
        res.x = c - 48;
        res.y = 2;
    }
    else if (specialCharMap.find(c) != specialCharMap.end())
    {
        res.x = specialCharMap[c];
        res.y = 2;
    }

    return res;
}