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
    std::array<std::unique_ptr<Item>, 5>* items;

public:
    Inventory(StateStack& stateStack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
};

