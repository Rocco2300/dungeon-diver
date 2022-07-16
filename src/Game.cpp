#include "Game.h"

#include <iostream>
#include <fstream>

#include "AssetManager.h"

Game::Game()
{
    srand(time(NULL));

    clock.restart();

    window.create(sf::VideoMode(size * scale, size * scale), "Dungeon Diver");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    if (!texture.create(size, size)) 
        std::cerr << "Error creating render texture!\n";

    tileset.create(AssetManager::getTexture("img/tiles.png"), {8, 8});

    world.create(tileset);
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

void Game::pollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            world.keyPressed(event.key.code);
        }
    }
}

void Game::update(sf::Time dt)
{
    world.update(dt);
}

void Game::draw()
{
    texture.clear();
    texture.draw(world);
    texture.display();

    sf::Sprite spr;
    spr.setTexture(texture.getTexture());
    spr.setScale({scale, scale});

    window.clear();
    window.draw(spr);
    window.display();
}