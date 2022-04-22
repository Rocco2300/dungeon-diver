#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
private:
    float t;
    bool finished;

    std::vector<int> dirBuf;

    int dirX[4] = {0, 1, 0, -1};
    int dirY[4] = {-1, 0, 1, 0};

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

    void move(int dir);

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    void animate(float animationSpeed);
};

