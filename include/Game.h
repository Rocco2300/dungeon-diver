#pragma once

#include "World.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::RenderTexture texture;
    float scale = 4.f;
    int size = 8 * 16;

    sf::Clock clock;
    sf::Time dt;

    Tileset tileset;

    World world;

public:
    Game();
    void run();
private:
    void pollEvents();
    void update(sf::Time dt);
    void draw();
};

