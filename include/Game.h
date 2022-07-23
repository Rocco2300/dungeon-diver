#pragma once

#include "World.h"
#include "State.h"

class Game : public State
{
private:
    World world;
    Tileset tileset;

public:
    Game() = default;
    Game(StateStack& stateStack, Context& context);

    bool handleEvent(const sf::Event& event);
    bool update(sf::Time dt);
    void draw();
};

