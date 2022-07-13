#include "AssetManager.h"

sf::Texture& AssetManager::get(std::string id)
{
    if (textureHolder.isLoaded(id))
        return textureHolder.get(id);
    
    textureHolder.load(id, id);
    return textureHolder.get(id);
}

void AssetManager::load(std::string id)
{
    if (textureHolder.isLoaded(id))
        return;

    textureHolder.load(id, id);
}