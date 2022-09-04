#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "World.h"
#include "StateIdentifiers.h"

class StateStack;

struct Context
{
    World* world;
    sf::RenderTexture* texture;
};

class State  
{
public:
    using Ptr = std::unique_ptr<State>;

protected:
//    sf::RenderTexture* texture;
    Context context;
    StateStack* stateStack;

public:
    State(StateStack& stateStack, Context context);
    virtual ~State() = default;

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPop();
    void requestStackClear();
    void requestStackPush(StateID stateID);
};
