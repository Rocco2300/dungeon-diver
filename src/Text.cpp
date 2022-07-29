#include "Text.h"

Text::Text() : width(8), height(8), letterSpacing(1), text("")
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
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(str.length() * 4);

    for (size_t i = 0; i < str.length(); i++)
    {
        int idx, tx{}, ty{};
        if (str[i] >= 97 && str[i] <= 122)
        {
            idx = str[i] - 97;
            tx = idx;
            ty = 0;
        }
        else if (str[i] >= 65 && str[i] <= 90)
        {
            idx = str[i] - 65;
            tx = idx;
            ty = 1;
        }

        auto* quad = &vertices[i * 4];

        quad[0].position = sf::Vector2f(i * width + i * letterSpacing, 0);
        quad[1].position = sf::Vector2f((i + 1) * width + i * letterSpacing, 0);
        quad[2].position = sf::Vector2f((i + 1) * width + i * letterSpacing, height);
        quad[3].position = sf::Vector2f(i * width + i * letterSpacing, height);

        quad[0].texCoords = sf::Vector2f(tx * width, ty * height);
        quad[1].texCoords = sf::Vector2f((tx + 1) * width, ty * height);
        quad[2].texCoords = sf::Vector2f((tx + 1) * width, (ty + 1) * height);
        quad[3].texCoords = sf::Vector2f(tx * width, (ty + 1) * height);
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

