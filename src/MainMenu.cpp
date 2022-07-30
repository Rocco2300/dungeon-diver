#include "MainMenu.h"

#include "StateStack.h"
#include "AssetManager.h"

#include <iostream>
#include <functional>

MainMenu::MainMenu(StateStack& stateStack, sf::RenderTexture& texture)
    : State(stateStack, texture)
{
    auto& containerBG = guiContainer.getBackgoundRef();
    guiContainer.setPosition({5, 5});
    containerBG.setFillColor(sf::Color::Black);
    containerBG.setSize({30, 30});
    // containerBG.setOutlineThickness(1.f);
    // containerBG.setOutlineColor(sf::Color::White);

    auto button1 = std::make_shared<GUI::Button<std::function<void()>>>();
    button1->setCallback([&stateStack] ()
    {   
        std::cout << "Pressed1\n";
        stateStack.popState();
        stateStack.pushState(StateID::Game);
    });
    auto& buttonBG1 = button1->getRectangleRef();
    button1->setPosition({0.f, 0.f});
    buttonBG1.setFillColor(sf::Color::Black);
    buttonBG1.setOutlineColor(sf::Color::White);
    buttonBG1.setSize({24.f, 8.f});
    button1->setText("Play");

    // TODO: add something
    auto button2 = std::make_shared<GUI::Button<std::function<void()>>>();
    button2->setCallback([&stateStack] ()
    {   
        std::cout << "Pressed2\n";
        stateStack.popState();
    });
    auto& buttonBG2 = button2->getRectangleRef();
    button2->setPosition({0.f, 10.f});
    buttonBG2.setFillColor(sf::Color::Black);
    buttonBG2.setOutlineColor(sf::Color::White);
    buttonBG2.setSize({24.f, 8.f});
    button2->setText("Exit");

    guiContainer.pack(button1);
    guiContainer.pack(button2);
}

bool MainMenu::handleEvent(const sf::Event& event)
{
    guiContainer.handleEvent(event);

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

