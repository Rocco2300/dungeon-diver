#pragma once

#include <SFML/Graphics.hpp>

#include "StateIdentifiers.h"

class StateStack;
class Context;

class State  
{
public:
    using Ptr = std::unique_ptr<State>;

protected:
    StateStack* stateStack;
    Context* context;

public:
    State(StateStack& stateStack, Context& context);
    virtual ~State() = default;

    virtual bool handleEvent(const sf::Event& event) = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual void draw() = 0;

protected:
    void requestStackPush(StateID stateID);
    void requestStackClear();
    void requestStackPop();
};
