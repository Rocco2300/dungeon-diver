#include "MainMenu.h"

#include "StateStack.h"

MainMenu::MainMenu(StateStack& stateStack, sf::RenderTexture& texture)
    : State(stateStack, texture)
{
    rect.setFillColor(sf::Color::Green);
    rect.setSize({36.f, 26.f});
}

bool MainMenu::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        stateStack->popState();
        stateStack->pushState(StateID::Game);
    }

    return false;
}

bool MainMenu::update(sf::Time dt)
{
    return false;
}

void MainMenu::draw()
{
    texture->draw(rect);
}

