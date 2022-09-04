#pragma once

#include "Item.h"
#include "State.h"
#include "Container.h"

#include <array>
#include <memory>

class Inventory : public State
{
private:
    GUI::Container gui;

    int selectedItem;
    ItemContainer* items;

public:
    Inventory(StateStack& stateStack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    void updateButtonLabels();
};

