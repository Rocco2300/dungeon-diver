#include "SoundManager.h"

#include "AssetManager.h"

void SoundManager::playSound(std::string soundId)
{
    std::unique_ptr<sf::Sound> sound;
    sound->setBuffer(AssetManager::getBuffer(soundId));
    sound->setLoop(false);
    sound->play();
    sounds.push_back(std::move(sound));
}

void SoundManager::cleanSounds()
{
    for (int i = sounds.size() - 1; i >= 0; i--)
    {
        if (sounds[i]->getStatus() == sf::Sound::Status::Stopped)
        {
            sounds.erase(sounds.begin() + i);
        }
    }
}