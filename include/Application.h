#pragma once

#include "Game.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "StateStack.h"

class Application
{
private:
    // Game* game;
    StateStack* stateStack;

    sf::RenderWindow window;
    sf::RenderTexture texture;
    float scale;
    int size;

    sf::Clock clock;
    sf::Time dt;
public:
    Application();

    void run(); 
    inline sf::RenderTexture& getRenderTex() { return texture; }
private:
    void pollEvents();
    void update();
    void draw();

    void registerStates();
};
