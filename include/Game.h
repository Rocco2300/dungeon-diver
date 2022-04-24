#pragma once

#include "Player.h"
#include "Tile.h"

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
    std::vector<sf::Vector2f> moveBuf;

    float dirX[4] = {0.f, 1.f, 0.f, -1.f};
    float dirY[4] = {-1.f, 0.f, 1.f, 0.f};

    sf::RenderWindow window;
    sf::RenderTexture texture;
    float scale = 4.f;
    int size = 8 * 16;

    sf::Clock clock;
    sf::Time dt;

    Player player;

    Tileset tileset;
    std::vector<Tile> map;
public:
    Game();
    void run();
private:
    void loadMap(const char* path);

    void handleInput(sf::Keyboard::Key key);

    void pollEvents();
    void update(sf::Time dt);
    void draw();
};

