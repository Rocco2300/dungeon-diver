#pragma once

#include "Text.h"
#include "Component.h"
#include "AssetManager.h"

enum class TextAllign
{
    Left,
    Center,
    Right
};

namespace GUI
{

class Label : public Component
{
private:
    Text text;
    TextAllign allignment;

public:
    Label() 
        : text(AssetManager::getTexture("font"), 3, 5, "")
        , allignment(TextAllign::Left) { }

    void setAllignment(TextAllign allignment);
    void setText(std::string str);

    bool isSelectable() const;
    void handleEvent(const sf::Event& event);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void applyAllignment();
};

};