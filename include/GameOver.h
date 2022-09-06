#pragma once

#include "Container.h"
#include "State.h"

class GameOver : public State
{
private:
    sf::Image   backgroundImage;
    sf::Sprite  backgroudSprite;
    sf::Texture backgroundTexture;

    GUI::Container container;

public:
    GameOver(StateStack& stateStack, Context context);

    void draw();
    bool update(sf::Time dt);
    bool handleEvent(const sf::Event& event);

private:
    void initUI();
};