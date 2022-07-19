#include "AssetManager.h"

#include <cassert>

sf::Texture& AssetManager::getTexture(std::string id)
{
    if (textureHolder.isLoaded(id))
        return textureHolder.get(id);
    
    textureHolder.load(id, pathPrefix + id + pathPostfix);
    return textureHolder.get(id);
}

void AssetManager::loadTexture(std::string id)
{
    if (textureHolder.isLoaded(id))
        return;

    textureHolder.load(id, pathPrefix + id + pathPostfix);
}

sf::SoundBuffer& AssetManager::getBuffer(SoundID id)
{
    if (bufferHolder.isLoaded(id))
        return bufferHolder.get(id);

    bufferHolder.load(id, soundPaths[id]);
    return bufferHolder.get(id);
}

void AssetManager::loadBuffer(SoundID id, const char* path)
{
    if (bufferHolder.isLoaded(id))
        return;

    bufferHolder.load(id, path);
}