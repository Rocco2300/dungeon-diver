#include "Container.h"

#include "AssetManager.h"
#include "Lerp.h"

namespace GUI
{

Container::Container()
    : selectedChild{-1}
{
    time      = 0.f;
    fadeSpeed = 2.f;
    lerpSpeed = 12.f;

    speed = lerpSpeed;

    doneFading  = true;
    doneScaling = true;
    doneLerping = true;

    arrowSelector.setTexture(AssetManager::getTexture("gui_elements"));
    arrowSelector.setTextureRect({0, 0, 8, 8});
    arrowSelector.setOrigin(4, 0);
}

void Container::pack(Component::Ptr component)
{
    children.push_back(component);

    if (!hasSelection() && component->isSelectable())
    {
        select(children.size() - 1);

        if (hasArrowSelector)
        {
            auto pos = children[selectedChild]->getPosition();

            arrowStart  = sf::Vector2f(pos);
            arrowTarget = sf::Vector2f(pos);

            arrowSelector.setPosition(pos);
        }
    }
}

Component::Ptr Container::getNthChild(int index) { return children[index]; }

void Container::setTransition(bool value)
{
    hasTransition = value;
    doneScaling   = !hasTransition;
}

void Container::setArrowSelector(bool value) { hasArrowSelector = value; }

void Container::setSize(sf::Vector2f size)
{
    this->size  = size;
    targetSize  = size.y;
    currentSize = 0.f;
}

bool Container::isSelectable() const { return false; }

void Container::update(sf::Time dt)
{
    if (doneFading && doneLerping && doneScaling)
    {
        if (!events.empty())
        {
            handleEventImpl(events.front());
            events.pop();
        }

        return;
    }

    if (!hasArrowSelector || !hasTransition) return;

    time += dt.asSeconds() * speed;

    if (time >= 1.f) time = 1.f;

    if (!doneFading)
    {
        if (time <= 0.5f)
            arrowSelector.setColor(
                    sf::Color(255, 255, 255, 1.f - (time * 2.f) * 255));
        else
        {
            arrowSelector.setPosition(arrowTarget);
            arrowSelector.setColor(
                    sf::Color(255, 255, 255, (time - 0.5f) * 2.f * 255));
        }
    }

    if (!doneLerping)
        arrowSelector.setPosition(lerp(arrowStart, arrowTarget, time));

    if (!doneScaling) { int size = lerp(currentSize, targetSize, t); }

    if (time == 1.f)
    {
        doneFading  = true;
        doneScaling = true;
        doneLerping = true;
    }
}

void Container::handleEvent(const sf::Event& event)
{
    if (!doneFading || !doneLerping)
    {
        events.push(event);
        return;
    }

    handleEventImpl(event);
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform transform;
    transform.translate(pos);
    states.transform *= transform;
    target.draw(background, states);

    for (auto& child: children)
    {
        if (hasArrowSelector && child->isSelected())
            target.draw(arrowSelector, states);

        target.draw(*child, states);
    }
}

bool Container::hasSelection() const { return selectedChild >= 0; }

bool Container::isArrowTargetOpposite() const
{
    if ((selectedChild == 0 && prevSelectedChild == children.size() - 1) ||
        (selectedChild == children.size() - 1 && prevSelectedChild == 0))
        return true;

    return false;
}

void Container::select(size_t index)
{
    if (children[index]->isSelectable())
    {
        if (hasSelection()) children[selectedChild]->deselect();

        children[index]->select();
        selectedChild = index;
    }
}

void Container::handleEventImpl(const sf::Event& event)
{
    if (hasSelection() && children[selectedChild]->isActive())
    {
        children[selectedChild]->handleEvent(event);
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            selectPrevious();

            if (hasArrowSelector) setArrowTarget();
        }
        else if (event.key.code == sf::Keyboard::S)
        {
            selectNext();

            if (hasArrowSelector) setArrowTarget();
        }
        else if (
                event.key.code == sf::Keyboard::Return ||
                event.key.code == sf::Keyboard::E)
        {
            if (hasSelection()) children[selectedChild]->activate();
        }
    }
}

void Container::selectNext()
{
    if (!hasSelection()) return;

    int next = selectedChild;
    do next = (next + 1) % children.size();
    while (!children[next]->isSelectable());

    prevSelectedChild = selectedChild;
    select(next);
}

void Container::selectPrevious()
{
    if (!hasSelection()) return;

    // Search previous component that is selectable, wrap around if necessary
    int prev = selectedChild;
    do prev = (prev + children.size() - 1) % children.size();
    while (!children[prev]->isSelectable());

    // Select that component
    prevSelectedChild = selectedChild;
    select(prev);
}

void Container::setArrowTarget()
{
    if (!isArrowTargetOpposite())
    {
        speed       = lerpSpeed;
        doneLerping = false;
    }
    else
    {
        speed      = fadeSpeed;
        doneFading = false;
    }

    time = 0.f;

    arrowStart  = arrowSelector.getPosition();
    arrowTarget = children[selectedChild]->getPosition();
}

}// namespace GUI