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
    Game(Context& context);

    void handleEvent(const sf::Event& event);
    void update(sf::Time dt);
    void draw();
};

