#include "Game.h"

#include <iostream>
#include <fstream>

#include "AssetManager.h"

Game::Game(StateStack& stateStack, sf::RenderTexture& texture)
    : State(stateStack, texture)
{
    tileset.create(AssetManager::getTexture("tiles"), {8, 8});
    world.create(tileset);
}

bool Game::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        world.keyPressed(event.key.code);
    }

    return false;
}

bool Game::update(sf::Time dt)
{
    world.update(dt);

    return false;
}

void Game::draw()
{
    texture->draw(world);
}