#pragma once

#include <SFML/Graphics.hpp>

class Context;

class State  
{
private:
    Context* context;
public:
    State(Context& context);
    virtual ~State() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw() = 0;
};
