#pragma once

#include "State.h"
#include "Container.h"

class GameOver : public State
{
private:
    sf::Image backgroundImage;
    sf::Texture backgroundTexture;
    sf::Sprite backgroudSprite;

    GUI::Container container;

public:
    GameOver(StateStack& stateStack, sf::RenderTexture& texture);

    void draw();
    bool update(sf::Time dt);
    bool handleEvent(const sf::Event& event);

private:
    void initUI();
};