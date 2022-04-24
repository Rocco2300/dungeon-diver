#pragma once

#include <functional>
#include <vector>

#include "Tileset.h"

class Player : public sf::Drawable
{
private:
    float t;
    float flip;
    float frame;

    sf::Vector2f pos;
    sf::Vector2f offS;
    sf::Vector2f off;

    Tileset sprite;
    sf::Sprite currFrame;

    std::function<void()> animation;
public:
    Player();
    Player(sf::Vector2f pos);

    void move(sf::Vector2f o);
    void bump(sf::Vector2f o);

    bool notMoving();
    sf::Vector2f getPosition();

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    void animate(float animationSpeed);
    void animateMove();
    void animateBump();
};

