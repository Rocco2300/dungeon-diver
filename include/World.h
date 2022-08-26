#pragma once

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

    bool playerTurn;
    bool nextLevel;

    sf::Time moveTime;

public:
    World() = default;
    void create(Map& map, Player& player, std::vector<Entity*>& entities);

    int getPlayerLife();

    bool goNextLevel();
    bool isPlayerTurn();
    bool isWall(Entity* caller, sf::Vector2i pos);
    bool isOccupied(Entity* caller, sf::Vector2i pos);

    sf::Vector2i getPlayerPos();
    std::vector<Entity*>& getEntities();

    void endTurn(Entity* entity);
    void setNextLevel(bool value);

    void keyPressed(sf::Keyboard::Key key);

    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


