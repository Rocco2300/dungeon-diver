#include "AssetManager.h"

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

sf::SoundBuffer& AssetManager::getBuffer(std::string id)
{
    if (bufferHolder.isLoaded(id))
        return bufferHolder.get(id);
    
    bufferHolder.load(id, id);
    return bufferHolder.get(id);
}

void AssetManager::loadBuffer(std::string id)
{
    if (bufferHolder.isLoaded(id))
        return;

    bufferHolder.load(id, id);
}