#pragma once

#include <functional>
#include <vector>

#include "Entity.h"

class World;

class Player : public Entity
{
private:
    World* world;

    std::vector<sf::Vector2f> moves;
public:
    Player();
    void init(World& world);

    void onKeyPressed(sf::Keyboard::Key key);
    void update(sf::Time dt);
};

