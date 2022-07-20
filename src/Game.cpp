#include "Game.h"

#include <iostream>
#include <fstream>

#include "AssetManager.h"

Game::Game(sf::RenderWindow& window)
{
    this->window = &window;

    tileset.create(AssetManager::getTexture("tiles"), {8, 8});
    world.create(tileset);
}

void Game::pollEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();

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

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(world, states);
}