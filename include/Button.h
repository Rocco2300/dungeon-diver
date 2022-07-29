#pragma once

#include "Text.h"
#include "Component.h"
#include "AssetManager.h"

#include <iostream>
#include <memory>
#include <functional>

#include <SFML/Graphics.hpp>

namespace GUI
{

template <typename Callback>
class Button : public Component
{
public:
    using Ptr = std::shared_ptr<Button>;

private:    
    Text text;
    sf::RectangleShape background;

    Callback callback;

public:
    Button() : text(AssetManager::getTexture("font"), 3, 5, "") { }

    sf::RectangleShape& getRectangleRef()
    {
        return background;
    }

    void setCallback(Callback callback)
    {
        this->callback = callback;
    }

    void setText(std::string txt)
    {
        text.setString(txt);

        int tx = (background.getSize().x - text.getSize().x) / 2;
        int ty = (background.getSize().y - text.getSize().y) / 2;
        text.setPosition(sf::Vector2f(tx, ty));
    }

    void setPosition(sf::Vector2f pos)
    {
        this->pos = pos;
        text.setPosition(pos);

    }

    virtual bool isSelectable() const
    {
        return true;
    }

    virtual void select()
    {
        Component::select();
        background.setOutlineThickness(1.f);
    }

    virtual void deselect()
    {
        Component::deselect();  
        background.setOutlineThickness(0.f);
    }

    virtual void activate()
    {
        Component::activate();
        callback();
    }

    virtual void deactivate()
    {
        Component::deactivate();
        // callback();
    }

    virtual void handleEvent(const sf::Event& event)
    {
        Component::deactivate();
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::Transform transform;
        transform.translate(pos);
        states.transform *= transform;

        target.draw(background, states);
        target.draw(text, states);
    }
};

};