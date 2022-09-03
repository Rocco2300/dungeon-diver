#include "MainMenu.h"

#include "StateStack.h"

#include <functional>

MainMenu::MainMenu(StateStack& stateStack, sf::RenderTexture& texture)
    : State(stateStack, texture)
{
    auto& containerBG = guiContainer.getBackgoundRef();
    guiContainer.setPosition({5, 5});
    guiContainer.setArrowSelector(true);

    containerBG.setFillColor(sf::Color::Black);
    containerBG.setSize({30, 30});

    auto button1 = std::make_shared<GUI::Button<std::function<void()>>>();
    button1->setCallback([&stateStack] ()
    {   
        stateStack.popState();
        stateStack.pushState(StateID::Game);
    });
    button1->setPosition({0.f, 0.f});
    button1->setSize({24, 8});
    button1->setText("Play");

    auto button2 = std::make_shared<GUI::Button<std::function<void()>>>();
    button2->setCallback([&stateStack] ()
    {   
        stateStack.popState();
    });
    button2->setPosition({0.f, 10.f});
    button2->setSize({24, 8});
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

