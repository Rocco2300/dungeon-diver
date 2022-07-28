#include "MainMenu.h"

#include "StateStack.h"

MainMenu::MainMenu(StateStack& stateStack, sf::RenderTexture& texture)
    : State(stateStack, texture)
{
    guiContainer.setPosition({5, 5});
    auto& containerBG = guiContainer.getBackgoundRef();
    containerBG.setFillColor(sf::Color::Black);
    containerBG.setSize({30, 30});
    containerBG.setOutlineThickness(2.f);
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

