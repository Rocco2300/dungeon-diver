#pragma once

#include <vector>
#include <memory>
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
};

