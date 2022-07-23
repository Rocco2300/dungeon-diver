#pragma once

#include "Game.h"

class Context
{
private:
    Game* game;

    sf::RenderWindow window;
    sf::RenderTexture texture;
    float scale = 4.f;
    int size = 8 * 16;

    sf::Clock clock;
    sf::Time dt;
public:
    Context();

    void run(); 
    inline sf::RenderTexture& getRenderTex() { return texture; }
private:
    void pollEvents();
    // void update(sf::Time dt);
    void draw();
};
