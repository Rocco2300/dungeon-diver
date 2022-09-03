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
    sf::Sprite arrowSelector;
    sf::RectangleShape background;

    std::vector<Component::Ptr> children;

    float time;
    float speed;
    float timeStep;
    float fadeSpeed;
    float lerpSpeed;

    int selectedChild;
    int prevSelectedChild;

    bool doneFading;
    bool doneLerping;
    bool hasArrowSelector;

    sf::Vector2f arrowStart;
    sf::Vector2f arrowTarget;

public:
    Container();

    inline sf::RectangleShape& getBackgoundRef() { return background; } 

    void pack(Component::Ptr component);
    Component::Ptr getNthChild(int index);

    void setArrowSelector(bool value);

    virtual bool isSelectable() const;

            void update(sf::Time dt);
    virtual void handleEvent(const sf::Event& event);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    bool hasSelection() const;
    bool isArrowTargetOpposite() const;

    void select(size_t index);

    void selectNext();
    void selectPrevious();
    void setArrowTarget();
};

}

