#include "MainMenu.h"

#include "StateStack.h"

MainMenu::MainMenu(StateStack& stateStack, sf::RenderTexture& texture)
    : State(stateStack, texture)
{
    auto& containerBG = guiContainer.getBackgoundRef();
    guiContainer.setPosition({5, 5});
    containerBG.setFillColor(sf::Color::Black);
    containerBG.setSize({30, 30});
    containerBG.setOutlineThickness(1.f);
    containerBG.setOutlineColor(sf::Color::White);
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
    texture->draw(guiContainer);
}

