#pragma once

#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>

class AssetManager
{
private:
    inline static ResourceHolder<sf::Texture, std::string> textureHolder;
public:
    AssetManager() = default;
    ~AssetManager() = default;

    static sf::Texture& getTexture(std::string id);
    static void loadTexture(std::string id);
};
