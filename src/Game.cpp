#include "Game.h"

#include <iostream>
#include <fstream>

Game::Game()
{
    clock.restart();

    window.create(sf::VideoMode(size * scale, size * scale), "Dungeon Diver");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    if (!texture.create(size, size))
        std::cerr << "Error creating render texture!\n";

    tileset.create("img/tiles.png", {8, 8});

    loadMap("map.txt");
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

void Game::loadMap(const char* path)
{
    std::ifstream in(path);

    int x;
    for (int i = 0; i < 16; i++)
    {
        std::vector<int> temp;
        for (int j = 0; j < 16; j++)
        {
            in >> x;

            Tile tile;
            tile.setTileset(tileset);
            tile.setID(x);
            tile.setWalkable((x == 0 || x == 1 || x == 9 || x == 10));
            tile.setInteractable((x == 3 || x == 5));

            map.push_back(tile);
        }
    }

    in.close();
}

void Game::handleInput(sf::Keyboard::Key key)
{
    auto it = keyMap.find(key);
            
    if (it != keyMap.end())
    {
        auto idx = keyMap[key];

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
        
        int idx = (mov.y + pos.y) * 16 + (mov.x + pos.x); 
        auto dest = map[idx];

        if (dest.isWalkable())
            player.move({mov.x, mov.y});
        else
        {
            player.bump({mov.x, mov.y});

            if (dest.isInteractable())
                std::cout << "Interact!" << std::endl;
        }
    }

    player.update(dt);
}

void Game::draw()
{
    texture.clear();
    for (size_t i = 0; i < map.size(); i++)
    {
        int x = i % 16;
        int y = i / 16;

        sf::Transform transform;
        transform.translate(x * 8, y * 8);
        sf::RenderStates states;
        states.transform = transform;

        texture.draw(map[i], states);
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