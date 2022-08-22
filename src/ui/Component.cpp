#include "Component.h"

namespace GUI
{

bool Component::isSelected() const 
{
    return selected;
}

void Component::select()
{
    selected = true;
}

void Component::deselect()
{
    selected = false;
}

bool Component::isActive() const
{
    return active;
}

void Component::activate()
{
    active = true;
}

void Component::deactivate()
{
    active = false;
}

};