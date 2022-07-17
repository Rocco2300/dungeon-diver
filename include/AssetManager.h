#pragma once

#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class SoundFX
{
    Hit,
    Move
};

class AssetManager
{
private:
    inline static ResourceHolder<sf::Texture, std::string> textureHolder;
    inline static ResourceHolder<sf::SoundBuffer, SoundFX> bufferHolder;
public:
    AssetManager() = default;
    ~AssetManager() = default;

    static sf::Texture& getTexture(std::string id);
    static void loadTexture(std::string id);

    static sf::SoundBuffer& getBuffer(SoundFX id);
    static void loadBuffer(SoundFX id, const char* path);
};
