#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

namespace GUI
{

class Component : public sf::Drawable
{
public:
    using Ptr = std::shared_ptr<Component>;

protected: 
    sf::Vector2f pos;
    sf::Vector2f size;

private:
    bool active;
    bool selected;

public:
    Component() : active{false}, selected{false} { }
    virtual ~Component() = default;

    inline virtual sf::Vector2f getSize() { return size; };
    inline virtual void setSize(sf::Vector2f size) { this->size = size; };
    inline virtual sf::Vector2f getPosition() { return pos; };
    inline virtual void setPosition(sf::Vector2f pos) { this->pos = pos; };

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
