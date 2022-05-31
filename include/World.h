#pragma once

#include "Spawner.h"
#include "Player.h"
#include "Map.h"

class World : public sf::Drawable
{
private:
    Tileset* tileset;

    Spawner spawner;
    std::vector<Entity*> entities;
    Player player;

    bool playerTurn;

    sf::Time moveTime;
public:
    Map map;

public:
    World() = default;
    void create(Tileset& tileset);

    bool isWall(Entity* caller, sf::Vector2i pos);
    bool isOccupied(Entity* caller, sf::Vector2i pos);
    bool isPlayerTurn();
    sf::Vector2i getPlayerPos();
    std::vector<Entity*>& getEntities();

    void endTurn(Entity* entity);

    void keyPressed(sf::Keyboard::Key key);

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


