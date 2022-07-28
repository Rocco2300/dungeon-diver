#include "Container.h"

void GUI::Container::pack(Component::Ptr component)
{
    children.push_back(component);

    if (!hasSelection() && component->isSelectable())
        select(children.size() - 1);
}

bool GUI::Container::isSelectable() const
{
    return false;
}

void GUI::Container::handleEvent(const sf::Event& event)
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
        else if (event.key.code == sf::Keyboard::Return)
        {
            if (hasSelection())
                children[selectedChild]->activate();
        }
    }
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.translate(pos);
    target.draw(background, states);

    for (auto& child : children)
    {
        target.draw(*child, states);
    }
}

bool GUI::Container::hasSelection() const
{
    return selectedChild >= 0;
}

void GUI::Container::select(size_t index)
{
    if (children[index]->isSelectable())
    {
        if (hasSelection())
            children[selectedChild]->deselect();
        
        children[index]->select();
        selectedChild = index;
    }
}

void GUI::Container::selectNext()
{
    if (!hasSelection())
        return;

    int next = selectedChild;
    do
        next = (next + 1) % children.size();
    while (!children[next]->isSelectable());

    select(next);
}

void GUI::Container::selectPrevious()
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

