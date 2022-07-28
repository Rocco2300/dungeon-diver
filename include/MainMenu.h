#pragma once

#include "Container.h"
#include "State.h"

class MainMenu : public State
{
private:
    GUI::Container guiContainer;
    
public:
    MainMenu(StateStack& stateStack, sf::RenderTexture& texture);

    void draw();
    bool update(sf::Time dt);
    bool handleEvent(const sf::Event& event);
};
