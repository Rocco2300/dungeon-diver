#pragma once

#include <SFML/Graphics.hpp>

#include "StateIdentifiers.h"

class StateStack;

class State  
{
public:
    using Ptr = std::unique_ptr<State>;

protected:
    sf::RenderTexture* texture;
    StateStack* stateStack;

public:
    State(StateStack& stateStack, sf::RenderTexture& texture);
    virtual ~State() = default;

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPop();
    void requestStackClear();
    void requestStackPush(StateID stateID);
};
