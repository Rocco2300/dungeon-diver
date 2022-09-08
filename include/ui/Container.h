#pragma once

#include "Component.h"

#include <queue>
#include <vector>

enum class Transition
{
    Open,
    Close
};

namespace GUI
{

class Container : public Component
{
public:
    using Ptr = std::shared_ptr<Container>;

private:
    sf::RectangleShape background;
    sf::Sprite         arrowSelector;
    sf::Color          backgroundColor;

    std::queue<sf::Event>       events;
    std::vector<Component::Ptr> children;

    float time;
    float speed;
    float fadeSpeed;
    float lerpSpeed;

    int selectedChild;
    int prevSelectedChild;

    bool doneFading;
    bool doneLerping;
    bool doneScaling;
    bool hasTransition;
    bool hasArrowSelector;

    float targetSize;
    float currentSize;

    sf::Vector2f arrowStart;
    sf::Vector2f arrowTarget;

public:
    Container();

    inline sf::RectangleShape& getBackgoundRef() { return background; }

    void           pack(Component::Ptr component);
    Component::Ptr getNthChild(int index);

    void setOutlineColor(sf::Color color);
    void setOutlineThickness(int thickness);
    void setBackgroundColor(sf::Color color);

    void setTransition(bool value);
    void setArrowSelector(bool value);
    void setSize(sf::Vector2f size) override;

    void transition(Transition transition);

    bool         isDoneScaling();
    virtual bool isSelectable() const;

    void         update(sf::Time dt);
    virtual void handleEvent(const sf::Event& event);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    bool hasSelection() const;
    bool isArrowTargetOpposite() const;

    void select(size_t index);
    void handleEventImpl(const sf::Event& event);

    void selectNext();
    void selectPrevious();
    void setArrowTarget();
};

}// namespace GUI
