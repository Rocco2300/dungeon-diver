#pragma once

#include <set>

#include "Spawner.h"
#include "Player.h"
#include "Map.h"

#include "MapGenerator.h"

class World : public sf::Drawable
{
private:
    Map* map;
    Player* player;
    std::vector<Entity*>* entities;
    std::set<Entity*> toMove;

    bool gameOver;
    bool playerTurn;
    bool nextLevel;

    sf::Time moveTime;

public:
    World() = default;
    void create(Map& map, Player& player, std::vector<Entity*>& entities);

    int getPlayerLife();

    bool isGameOver();
    bool goNextLevel();
    bool isPlayerTurn();
    bool canMove(Entity* caller);
    bool isWall(Entity* caller, sf::Vector2i pos);
    bool isOccupied(Entity* caller, sf::Vector2i pos);

    sf::Vector2i getPlayerPos();
    std::vector<Entity*>& getEntities();

    void endTurn(Entity* entity);
    void setGameOver(bool value);
    void setNextLevel(bool value);

    void keyPressed(sf::Keyboard::Key key);

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


