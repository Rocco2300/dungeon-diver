#pragma once

#include "State.h"

class MainMenu : public State
{
private:
    sf::RectangleShape rect;
    
public:
    MainMenu(StateStack& stateStack, sf::RenderTexture& texture);

    void draw();
    bool update(sf::Time dt);
    bool handleEvent(const sf::Event& event);
};
