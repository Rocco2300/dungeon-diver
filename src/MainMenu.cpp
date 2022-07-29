#include "MainMenu.h"

#include "StateStack.h"

#include <iostream>
#include <functional>

MainMenu::MainMenu(StateStack& stateStack, sf::RenderTexture& texture)
    : State(stateStack, texture)
{
    auto& containerBG = guiContainer.getBackgoundRef();
    guiContainer.setPosition({5, 5});
    containerBG.setFillColor(sf::Color::Black);
    containerBG.setSize({30, 30});
    containerBG.setOutlineThickness(1.f);
    containerBG.setOutlineColor(sf::Color::White);

    auto button1 = std::make_shared<GUI::Button<std::function<void()>>>();
    button1->setCallback([] ()
    {   
        std::cout << "Pressed1\n";
    });
    auto& buttonBG1 = button1->getRectangleRef();
    button1->setPosition({0.f, 0.f});
    buttonBG1.setFillColor(sf::Color::Black);
    buttonBG1.setOutlineColor(sf::Color::White);
    buttonBG1.setSize({8.f, 8.f});

    auto button2 = std::make_shared<GUI::Button<std::function<void()>>>();
    button2->setCallback([] ()
    {   
        std::cout << "Pressed2\n";
    });
    auto& buttonBG2 = button2->getRectangleRef();
    button2->setPosition({0.f, 10.f});
    buttonBG2.setFillColor(sf::Color::Black);
    buttonBG2.setOutlineColor(sf::Color::White);
    buttonBG2.setSize({8.f, 8.f});

    auto button3 = std::make_shared<GUI::Button<std::function<void()>>>();
    button3->setCallback([] ()
    {   
        std::cout << "Pressed3\n";
    });
    auto& buttonBG3 = button3->getRectangleRef();
    button3->setPosition({0.f, 21.f});
    buttonBG3.setFillColor(sf::Color::Black);
    buttonBG3.setOutlineColor(sf::Color::White);
    buttonBG3.setSize({8.f, 8.f});

    guiContainer.pack(button1);
    guiContainer.pack(button2);
    guiContainer.pack(button3);

    text.setString("button");
    text.setPosition({10.f, 10.f});
}

bool MainMenu::handleEvent(const sf::Event& event)
{
    guiContainer.handleEvent(event);
    // if (event.type == sf::Event::KeyPressed)
    // {
    //     stateStack->popState();
    //     stateStack->pushState(StateID::Game);
    // }

   return false;
}

bool MainMenu::update(sf::Time dt)
{
    return false;
}

void MainMenu::draw()
{
    texture->draw(guiContainer);
    texture->draw(text);
}

