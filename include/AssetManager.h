#pragma once

#include "ResourceHolder.h"

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
private:
    inline const static std::string imagePathPrefix = "img/";
    inline const static std::string soundPathPrefix = "sound/";
    inline const static std::string imagePathPostfix = ".png";
    inline const static std::string soundPathPostfix = ".wav";

    inline static ResourceHolder<sf::Texture, std::string> textureHolder;
    inline static ResourceHolder<sf::SoundBuffer, std::string> bufferHolder;
public:
    AssetManager() = default;
    ~AssetManager() = default;

    static sf::Texture& getTexture(const std::string& id);
    static void loadTexture(const std::string& id);

    static sf::SoundBuffer& getBuffer(const std::string& id);
    static void loadBuffer(const std::string& id, const char* path);
};
