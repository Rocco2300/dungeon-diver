#include "Component.h"

bool GUI::Component::isSelected() const 
{
    return selected;
}

void GUI::Component::select()
{
    selected = true;
}

void GUI::Component::deselect()
{
    selected = false;
}

bool GUI::Component::isActive() const
{
    return active;
}

void GUI::Component::activate()
{
    active = true;
}

void GUI::Component::deactivate()
{
    active = false;
}