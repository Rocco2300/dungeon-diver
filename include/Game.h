#pragma once

#include "World.h"

class Game
{
private:
    // std::map<sf::Keyboard::Key, int> keyMap = 
    // {
    //     { sf::Keyboard::W, 0 },
    //     { sf::Keyboard::D, 1 },
    //     { sf::Keyboard::S, 2 },
    //     { sf::Keyboard::A, 3 },
    // };
    // std::vector<sf::Vector2f> moveBuf;

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
    // void handleInput(sf::Keyboard::Key key);

    void pollEvents();
    void update(sf::Time dt);
    void draw();
};

