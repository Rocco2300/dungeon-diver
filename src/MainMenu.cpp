#include "MainMenu.h"

#include "Constants.h"
#include "StateStack.h"

#include <cmath>
#include <functional>

MainMenu::MainMenu(StateStack& stateStack, sf::RenderTexture& texture)
    : State(stateStack, texture)
{
    auto& containerBG = guiContainer.getBackgoundRef();
    guiContainer.setSize({43, 36});
    guiContainer.setArrowSelector(true);
    // Floor the position to avoid floating point error on low res
    guiContainer.setPosition({
        std::floor((WINDOW_SIZE - guiContainer.getSize().x) / 2),
        WINDOW_SIZE / 2
    });

    containerBG.setFillColor(sf::Color::Black);
    containerBG.setOutlineThickness(1);
    containerBG.setOutlineColor(sf::Color::White);
    containerBG.setSize({43, 36});

    auto button1 = std::make_shared<GUI::Button<std::function<void()>>>();
    button1->setCallback([&stateStack] ()
    {   
        stateStack.popState();
        stateStack.pushState(StateID::Game);
    });
    button1->setPosition({10.f, 4.f});
    button1->setSize({24, 8});
    button1->setText("Play");

    auto button2 = std::make_shared<GUI::Button<std::function<void()>>>();
    button2->setCallback([&stateStack] ()
    {
        std::cerr << "Not yet implemented :p\n";
    });
    button2->setPosition({4.f, 14.f});
    button2->setSize({36, 8});
    button2->setText("Options");

    auto button3 = std::make_shared<GUI::Button<std::function<void()>>>();
    button3->setCallback([&stateStack] ()
    {   
        stateStack.popState();
    });
    button3->setPosition({10.f, 24.f});
    button3->setSize({24, 8});
    button3->setText("Exit");

    guiContainer.pack(button1);
    guiContainer.pack(button2);
    guiContainer.pack(button3);
}

bool MainMenu::handleEvent(const sf::Event& event)
{
    guiContainer.handleEvent(event);

    return false;
}

bool MainMenu::update(sf::Time dt)
{
    guiContainer.update(dt);

    return false;
}

void MainMenu::draw()
{
    texture->draw(guiContainer);
}

