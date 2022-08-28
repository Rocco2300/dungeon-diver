#include "AssetManager.h"

#include <cassert>

sf::Texture& AssetManager::getTexture(const std::string& id)
{
    if (textureHolder.isLoaded(id))
        return textureHolder.get(id);

    textureHolder.load(
        id,
        IMG_PATH + id + imagePathPostfix
    );

    return textureHolder.get(id);
}

void AssetManager::loadTexture(const std::string& id)
{
    if (textureHolder.isLoaded(id))
        return;

    textureHolder.load(
        id,
        IMG_PATH + id + imagePathPostfix
    );
}

sf::SoundBuffer& AssetManager::getBuffer(const std::string& id)
{
    if (bufferHolder.isLoaded(id))
        return bufferHolder.get(id);

    bufferHolder.load(
        id,
        SOUND_PATH + id + soundPathPostfix
    );

    return bufferHolder.get(id);
}

void AssetManager::loadBuffer(const std::string& id)
{
    if (bufferHolder.isLoaded(id))
        return;

    bufferHolder.load(
        id,
        SOUND_PATH + id + soundPathPostfix
    );
}

sf::Font& AssetManager::getFont(const std::string& id)
{
    if (fontHolder.isLoaded(id))
        return fontHolder.get(id);

    fontHolder.load(
        id,
        FONT_PATH + id + fontPathPostfix
    );

    return fontHolder.get(id);
}

void AssetManager::loadFont(const std::string& id)
{
    if (fontHolder.isLoaded(id))
        return;

    fontHolder.load(
        id,
        FONT_PATH + id + fontPathPostfix
    );
}