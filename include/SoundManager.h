#pragma once

#include <vector>
#include <memory>
#include <string>

#include <SFML/Audio.hpp>

enum class SoundFX
{
    Hit,
    Move
};

class SoundManager
{
private:
    std::vector<std::unique_ptr<sf::Sound>> sounds;
public:
    SoundManager() = default;
    ~SoundManager() = default;

    void playSound(std::string soundId);
    void cleanSounds();
};

