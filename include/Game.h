#pragma once

#include "Player.h"

class Game
{
private:
    std::map<sf::Keyboard::Key, int> keyMap = 
    {
        { sf::Keyboard::W, 0 },
        { sf::Keyboard::D, 1 },
        { sf::Keyboard::S, 2 },
        { sf::Keyboard::A, 3 },
    };

    sf::RenderWindow window;
    sf::RenderTexture texture;
    float scale = 4.f;
    int size = 8 * 16;

    sf::Clock clock;
    sf::Time dt;

    Player player;

    sf::Texture tileSet;
    sf::Sprite tile;
    std::vector<std::vector<int>> map;
public:
    Game();
    void run();
private:
    std::vector<std::vector<int>> loadMap(const char* path);

    void pollEvents();
    void update(sf::Time dt);
    void draw();
};

