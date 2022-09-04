#pragma once

#include "Container.h"
#include "Button.h"
#include "State.h"
#include "Text.h"

class MainMenu : public State
{
private:
    GUI::Container guiContainer;
    
public:
    MainMenu(StateStack& stateStack, Context context);

    void draw();
    bool update(sf::Time dt);
    bool handleEvent(const sf::Event& event);
};
