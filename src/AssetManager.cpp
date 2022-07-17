#include "AssetManager.h"

#include <cassert>

sf::Texture& AssetManager::getTexture(std::string id)
{
    if (textureHolder.isLoaded(id))
        return textureHolder.get(id);
    
    textureHolder.load(id, id);
    return textureHolder.get(id);
}

void AssetManager::loadTexture(std::string id)
{
    if (textureHolder.isLoaded(id))
        return;

    textureHolder.load(id, id);
}

sf::SoundBuffer& AssetManager::getBuffer(SoundFX id)
{
    assert(bufferHolder.isLoaded(id));
    return bufferHolder.get(id);
}

void AssetManager::loadBuffer(SoundFX id, const char* path)
{
    if (bufferHolder.isLoaded(id))
        return;

    bufferHolder.load(id, path);
}