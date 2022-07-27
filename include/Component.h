#pragma once

#include <memory>

#include <SFML/Window/Event.hpp>

namespace GUI
{

class Component
{
public:
    using Ptr = std::shared_ptr<Component>;

private: 
    bool active;
    bool selected;

public:
    Component() : isActive{false}, isSelected{false} { }
    virtual ~Component() = default;

    virtual bool isSelectable() const = 0;
            bool isSelected() const;
    virtual void select();
    virtual void deselect();

    virtual bool isActive() const;
    virtual void activate();
    virtual void deactivate();

    virtual void handleEvent(const sf::Event& event) = 0;
};

};
