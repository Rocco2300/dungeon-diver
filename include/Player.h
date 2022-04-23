#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
private:
    float t;
    bool finished;

    sf::Vector2f pos;
    sf::Vector2f offS;
    sf::Vector2f off;

    bool flip;
    float frame;

    sf::Texture tex;
    sf::Sprite spr;
public:
    Player();
    Player(sf::Vector2f pos);

    void move(sf::Vector2f o);

    bool notMoving();
    sf::Vector2f getPosition();

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    void animate(float animationSpeed);
};

