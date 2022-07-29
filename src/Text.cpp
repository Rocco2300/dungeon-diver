#include "Text.h"

Text::Text() : texture(&AssetManager::getTexture("font")), text("")
{
}

Text::Text(std::string str) : texture(&AssetManager::getTexture("font")), text(str)
{
    setString(str);
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

        quad[0].position = sf::Vector2f(i * 3, 0);
        quad[1].position = sf::Vector2f((i + 1) * 3, 0);
        quad[2].position = sf::Vector2f((i + 1) * 3, 5);
        quad[3].position = sf::Vector2f(i * 3, 5);

        quad[0].texCoords = sf::Vector2f(tx * 3, ty * 5);
        quad[1].texCoords = sf::Vector2f((tx + 1) * 3, ty * 5);
        quad[2].texCoords = sf::Vector2f((tx + 1) * 3, (ty + 1) * 5);
        quad[3].texCoords = sf::Vector2f(tx * 3, (ty + 1) * 5);
    }
}

void Text::setPosition(sf::Vector2f pos)
{
    this->pos = pos;
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform translate;
    translate.translate(pos);

    states.texture = texture;
    states.transform = translate;

    target.draw(vertices, states);
}