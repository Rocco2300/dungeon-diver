#pragma once

#include "ResourceHolder.h"

#include <map>

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
    inline static std::map<SoundFX, std::string> soundPaths = 
    {
        {SoundFX::Hit, "sound/hit1.wav"},
        {SoundFX::Move, "sound/hit2.wav"}
    };

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
