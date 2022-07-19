#pragma once

#include <vector>
#include <memory>
#include <string>

#include <SFML/Audio.hpp>

#include "AssetManager.h"

class SoundManager
{
private:
    inline static std::vector<std::unique_ptr<sf::Sound>> sounds;
public:
    SoundManager() = default;
    ~SoundManager() = default;

    static void playSound(SoundID soundId);
    static void cleanSounds();
};

