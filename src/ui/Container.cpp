#include "Container.h"

#include "AssetManager.h"

namespace GUI
{

Container::Container() : selectedChild{-1}
{
    arrowSelector.setTexture(AssetManager::getTexture("gui_elements"));
    arrowSelector.setTextureRect({0, 0, 8, 8});
    arrowSelector.setOrigin(4, 0);
}

void Container::pack(Component::Ptr component)
{
    children.push_back(component);

    if (!hasSelection() && component->isSelectable())
        select(children.size() - 1);

    auto pos = children[selectedChild]->getPosition();
    arrowSelector.setPosition(pos);
}

Component::Ptr Container::getNthChild(int index)
{
    return children[index];
}

void Container::setArrowSelector(bool value)
{
    hasArrowSelector = value;
}

bool Container::isSelectable() const
{
    return false;
}

void Container::handleEvent(const sf::Event& event)
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
        }
        else if (event.key.code == sf::Keyboard::S)
        {
            selectNext();
        }
        else if (event.key.code == sf::Keyboard::Return ||
            event.key.code == sf::Keyboard::E)
        {
            if (hasSelection())
                children[selectedChild]->activate();
        }
    }

    auto pos = children[selectedChild]->getPosition();
    arrowSelector.setPosition(pos);
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform transform;
    transform.translate(pos);
    states.transform *= transform;
    target.draw(background, states);

    for (auto& child : children)
    {
        if (hasArrowSelector && child->isSelectable())
            target.draw(arrowSelector, states);

        target.draw(*child, states);
    }
}

bool Container::hasSelection() const
{
    return selectedChild >= 0;
}

void Container::select(size_t index)
{
    if (children[index]->isSelectable())
    {
        if (hasSelection())
            children[selectedChild]->deselect();
        
        children[index]->select();
        selectedChild = index;
    }
}

void Container::selectNext()
{
    if (!hasSelection())
        return;

    int next = selectedChild;
    do
        next = (next + 1) % children.size();
    while (!children[next]->isSelectable());

    select(next);
}

void Container::selectPrevious()
{
    if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = selectedChild;
	do
        prev = (prev + children.size() - 1) % children.size();
	while (!children[prev]->isSelectable());

	// Select that component
	select(prev);
}

}