#include "Game.h"

#include <iostream>
#include <fstream>

Game::Game()
{
    clock.restart();

    window.create(sf::VideoMode(size * scale, size * scale), "SFML works!");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    if (!texture.create(size, size))
        std::cerr << "Error creating render texture!\n";

    if(!tileSet.loadFromFile("img/tiles.png"))
        std::cerr << "error\n";

    tile.setTexture(tileSet);
    tile.setTextureRect({{0, 0}, {8, 8}});

    map = loadMap("map.txt");
}

void Game::run()
{
    while (window.isOpen())
    {
        dt = clock.restart();

        pollEvents();
        update(dt);
        draw();
    }
}

std::vector<std::vector<int>> Game::loadMap(const char* path)
{
    std::vector<std::vector<int>> map;
    std::ifstream in(path);

    int x;
    for (int i = 0; i < 16; i++)
    {
        std::vector<int> temp;
        for (int j = 0; j < 16; j++)
        {
            in >> x;

            temp.push_back(x);
        }
        map.push_back(temp);
    }

    in.close();
    return map;
}

void Game::handleInput(sf::Keyboard::Key key)
{
    auto it = keyMap.find(key);
            
    if (it != keyMap.end())
    {
        auto idx = keyMap[key];
        auto pos = player.getPosition();
        auto dest = map[dirY[idx] + pos.y][dirX[idx] + pos.x];

        if (player.notMoving() && dest != 2)
            player.move({dirX[idx], dirY[idx]});
        else if (!player.notMoving() && dest != 2)
            moveBuf.push_back({dirX[idx], dirY[idx]});
    }
}

void Game::pollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            handleInput(event.key.code);
        }
    }
}

void Game::update(sf::Time dt)
{
    if (!moveBuf.empty() && player.notMoving())
    {
        auto mov = moveBuf.front();
        moveBuf.erase(moveBuf.begin());

        auto pos = player.getPosition();
        auto dest = map[mov.y + pos.y][mov.x + pos.x];

        if (dest != 2)
            player.move(mov);
    }

    player.update(dt);
}

void Game::draw()
{
    texture.clear();
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            tile.setTextureRect({{map[i][j] * 8, 0}, {8, 8}});
            tile.setPosition(j * 8.f, i * 8.f);
            texture.draw(tile);
        }
    }

    texture.draw(player);
    texture.display();

    sf::Sprite spr;
    spr.setTexture(texture.getTexture());
    spr.setScale({scale, scale});

    window.clear();
    window.draw(spr);
    window.display();
}