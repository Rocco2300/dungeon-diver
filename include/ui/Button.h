#pragma once

#include "Label.h"
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
    TextLabel label;
    // sf::RectangleShape background;
    sf::Sprite selector;

    Callback callback;

public:
    Button()
    {
        selector.setTexture(AssetManager::getTexture("gui_elements"));
        selector.setTextureRect({0, 0, 8, 8});
        selector.setPosition({-4.f, 0.f});
    }

    void setCallback(Callback callback)
    {
        this->callback = callback;
    }

    void setText(std::string txt)
    {
        label.setText(txt);
        label.setAllignment(Allign::Center);
    }

    void setSize(sf::Vector2f size) override
    {
        this->size = size;
        label.setSize(size);
    }

    virtual bool isSelectable() const
    {
        return true;
    }

    virtual void select()
    {
        Component::select();
    }

    virtual void deselect()
    {
        Component::deselect();  
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

        // target.draw(background, states);
        if (isSelected())
            target.draw(selector, states);

        target.draw(label, states);
    }
};

}