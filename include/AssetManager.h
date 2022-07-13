#pragma once

#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>

class AssetManager
{
private:
    static ResourceHolder<sf::Texture, std::string> textureHolder;
public:
    AssetManager() = default;
    ~AssetManager() = default;

    static sf::Texture& get(std::string id);
    static void load(std::string id);
};
