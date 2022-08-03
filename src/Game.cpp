#include "Game.h"

#include <iostream>
#include <fstream>

#include "StateStack.h"
#include "AssetManager.h"

Game::Game(StateStack& stateStack, sf::RenderTexture& texture)
    : State(stateStack, texture)
{
    tileset.create(AssetManager::getTexture("tiles"), {8, 8});
    world.create(tileset);

    auto textLabel = std::make_shared<GUI::TextLabel>();
    textLabel->setSize({8, 8});
    // textLabel->setText("2");
    textLabel->setAllignment(Allign::Center);
    textLabel->setPosition({0, 0});

    auto spriteLabel = std::make_shared<GUI::SpriteLabel>();
    spriteLabel->setSize({8, 8});
    spriteLabel->setSprite("gui_elements");
    spriteLabel->setSpriteRect({16, 0, 8, 8});
    spriteLabel->setPosition({6, 0});

    container.setSize({16, 8});
    container.setPosition({2, 2});
    container.getBackgoundRef().setFillColor(sf::Color::Black);
    container.getBackgoundRef().setOutlineColor(sf::Color::White);
    container.getBackgoundRef().setOutlineThickness(1);
    container.getBackgoundRef().setSize({16, 8});
    
    container.pack(textLabel);
    container.pack(spriteLabel);
}

bool Game::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            stateStack->popState();
            stateStack->pushState(StateID::MainMenu);
        }
        world.keyPressed(event.key.code);
    }

    return false;
}

bool Game::update(sf::Time dt)
{
    world.update(dt);

    auto componentLabel = container.getNthChild(0);
    auto* hpLabel = dynamic_cast<GUI::TextLabel*>(componentLabel.get());
    if (hpLabel)
        hpLabel->setText(std::to_string(world.getPlayerLife()));

    return false;
}

void Game::draw()
{
    texture->draw(world);
    // texture->draw(hpLabel);
    texture->draw(container);
}