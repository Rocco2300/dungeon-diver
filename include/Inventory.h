#pragma once

#include "Container.h"
#include "Item.h"
#include "State.h"

#include <array>
#include <memory>

class Inventory : public State
{
private:
    int option;

    GUI::Container gui;
    ItemContainer* items;

public:
    Inventory(StateStack& stateStack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    void updateButtonLabels();
};
