#include "Game.h"

#include <iostream>
#include <fstream>

#include "AssetManager.h"

Game::Game(sf::RenderWindow& window)
{
    tileset.create(AssetManager::getTexture("tiles"), {8, 8});
    world.create(tileset);
}

void Game::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        world.keyPressed(event.key.code);
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