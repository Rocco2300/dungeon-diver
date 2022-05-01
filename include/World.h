#pragma once

#include "Slime.h"
#include "Player.h"
#include "Map.h"

class World : public sf::Drawable
{
private:
    bool playerTurn;

    sf::Time moveTime;

    Map map;
    Tileset* tileset;

    std::vector<Entity*> entities;
    Player player;
    Slime slime;
public:
    float dirX[4] = {0.f, 1.f, 0.f, -1.f};
    float dirY[4] = {-1.f, 0.f, 1.f, 0.f};
public:
    World();
    void create(Tileset& tileset);

    bool isWall(Entity* caller, sf::Vector2f pos);
    bool isOccupied(Entity* caller, sf::Vector2f pos);

    void keyPressed(sf::Keyboard::Key key);

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


