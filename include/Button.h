#pragma once

#include "Component.h"

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
    Callback callback;
    sf::RectangleShape background;

public:
    Button() = default;

    sf::RectangleShape& getRectangleRef()
    {
        return background;
    }

    void setCallback(Callback callback)
    {
        this->callback = callback;
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
        callback();
    }

    virtual void handleEvent(const sf::Event& event)
    {

    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // sf::Transform transform;
        // transform.translate(pos);
        // states.transform = transform;
        target.draw(background, states);
    }
};

};