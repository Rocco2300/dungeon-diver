#pragma once

#include "Component.h"

#include <vector>

namespace GUI
{

class Container : public Component
{
public:
    using Ptr = std::shared_ptr<Container>;

private:
    sf::RectangleShape background;

    std::vector<Component::Ptr> children;
    int selectedChild;

public:
    Container() : selectedChild{-1} { }

    inline sf::Vector2f getPosition() { return pos; }
    inline sf::RectangleShape& getBackgoundRef() { return background; } 
    inline void setPosition(sf::Vector2f pos) { this->pos = pos; background.setPosition(pos); }

    void pack(Component::Ptr component);

    virtual bool isSelectable() const;
    virtual void handleEvent(const sf::Event& event);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    bool hasSelection() const;
    void select(size_t index);
    void selectNext();
    void selectPrevious();
};

};

