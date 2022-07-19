#pragma once

#include "ResourceHolder.h"

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class SoundID
{
    Hit,
    Move
};

class AssetManager
{
private:
    inline const static std::string pathPrefix = "img/";
    inline const static std::string pathPostfix = ".png";

    inline static std::map<SoundID, std::string> soundPaths = 
    {
        {SoundID::Hit, "sound/hit1.wav"},
        {SoundID::Move, "sound/hit2.wav"}
    };

    inline static ResourceHolder<sf::Texture, std::string> textureHolder;
    inline static ResourceHolder<sf::SoundBuffer, SoundID> bufferHolder;
public:
    AssetManager() = default;
    ~AssetManager() = default;

    static sf::Texture& getTexture(std::string id);
    static void loadTexture(std::string id);

    static sf::SoundBuffer& getBuffer(SoundID id);
    static void loadBuffer(SoundID id, const char* path);
};
