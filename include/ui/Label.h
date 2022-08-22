#pragma once

#include "Text.h"
#include "Component.h"
#include "AssetManager.h"

enum class Allign
{
    Left,
    Center,
    Right
};

namespace GUI
{

class TextLabel : public Component
{
private:
    Text text;
    Allign allignment;

public:
    TextLabel() 
        : text(AssetManager::getTexture("font"), 3, 5, "")
        , allignment(Allign::Left) { }

    void setAllignment(Allign allignment);
    void setText(std::string str);

    bool isSelectable() const;
    void handleEvent(const sf::Event& event);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void applyAllignment();
};

class SpriteLabel : public Component
{
private:
    sf::Sprite sprite;
    Allign allignment;

public:
    SpriteLabel() 
        : allignment(Allign::Left) { }

    SpriteLabel(std::string spriteName)
        : sprite(AssetManager::getTexture(spriteName))
        , allignment(Allign::Left) { }

    SpriteLabel(std::string spriteName, sf::IntRect rect) 
        : sprite(AssetManager::getTexture(spriteName), rect)
        , allignment(Allign::Left) { }

    void setAllignment(Allign allignment);
    void setSprite(std::string spriteName);
    void setSpriteRect(sf::IntRect rect);

    bool isSelectable() const;
    void handleEvent(const sf::Event& event);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void applyAllignment();
};

};