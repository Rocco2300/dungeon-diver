#pragma once

#include <SFML/Graphics.hpp>

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

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool draw() = 0;

protected:
    void requestStackPush(StateID stateID);
    void requestStackClear();
    void requestStackPop();
};
