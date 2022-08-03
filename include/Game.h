#pragma once

#include "Label.h"
#include "Container.h"
#include "World.h"
#include "State.h"

class Game : public State
{
private:
    GUI::Container container;

    World world;
    Tileset tileset;

public:
    Game() = default;
    Game(StateStack& stateStack, sf::RenderTexture& texture);

    void draw();
    bool update(sf::Time dt);
    bool handleEvent(const sf::Event& event);
};

