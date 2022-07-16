#pragma once

#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
private:
    inline static ResourceHolder<sf::Texture, std::string> textureHolder;
    inline static ResourceHolder<sf::SoundBuffer, std::string> bufferHolder;
public:
    AssetManager() = default;
    ~AssetManager() = default;

    static sf::Texture& getTexture(std::string id);
    static void loadTexture(std::string id);

    static sf::SoundBuffer& getBuffer(std::string id);
    static void loadBuffer(std::string id);
};
