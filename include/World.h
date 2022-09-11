#pragma once

#include <set>

#include "Map.h"
#include "Player.h"
#include "Spawner.h"

#include "MapGenerator.h"

class World : public sf::Drawable
{
private:
    Map*                  map;
    Player*               player;
    std::vector<Entity*>* entities;

    int toMove;

    bool gameOver;
    bool nextLevel;

    sf::Time moveTime;

public:
    World() = default;
    void create(Map& map, Player& player, std::vector<Entity*>& entities);

    int getPlayerLife();

    bool isGameOver();
    bool goNextLevel();
    bool canMove(Entity* caller);
    bool isWall(Entity* caller, sf::Vector2i pos);
    bool isOccupied(Entity* caller, sf::Vector2i pos);

    void attack(Entity* caller, sf::Vector2i pos);
    void interact(Entity* caller, sf::Vector2i pos);

    Player&               getPlayerRef();
    sf::Vector2i          getPlayerPos();
    std::vector<Entity*>& getEntities();

    void endTurn(Entity* entity);
    void setGameOver(bool value);
    void setNextLevel(bool value);

    void keyPressed(sf::Keyboard::Key key);

    void         update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    bool isInBounds(sf::Vector2i pos);
};
