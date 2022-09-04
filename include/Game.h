#pragma once

#include "Label.h"
#include "Container.h"
#include "World.h"
#include "State.h"

#include "ItemFactory.h"

class Game : public State
{
private:
    GUI::Container hpDisplay;

    Map map;
    Spawner spawner;
    MapGenerator gen;
    std::vector<Entity*> entities;
    Player player;

    ItemFactory itemFact;

    World world;
    Tileset tileset;

public:
    Game() = default;
    Game(StateStack& stateStack, Context context);

    void draw();
    bool update(sf::Time dt);
    bool handleEvent(const sf::Event& event);

private:
    void initUI();
};

