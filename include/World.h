#pragma once

#include "Player.h"
#include "Map.h"

class World : public sf::Drawable
{
private:
    Map map;
    Tileset* tileset;

    Player player;
public:
    float dirX[4] = {0.f, 1.f, 0.f, -1.f};
    float dirY[4] = {-1.f, 0.f, 1.f, 0.f};
public:
    World();
    void create(Tileset& tileset);

    bool isEmpty(sf::Vector2f pos);

    void keyPressed(sf::Keyboard::Key key);

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


