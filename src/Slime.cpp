#include "Slime.h"

#include "World.h"
#include <random>
#include <iostream>

Slime::Slime()
{
    hp = 1;

    moveTime = sf::seconds(.5f);

    sprite.create("img/slime.png", {8, 8});
}

void Slime::init(World& world)
{
    this->world = &world;
}

void Slime::update(sf::Time dt)
{
    bool x = playerLos();

    if (!world->isPlayerTurn())
        moveTime -= dt;

    if (!world->isPlayerTurn() && moveTime.asSeconds() <= 0)
    {
        int randDir;
        sf::Vector2f dirOff;

        do 
        {
            randDir = rand() % 4;

            dirOff = sf::Vector2f(world->dirX[randDir], world->dirY[randDir]);
        } while (world->isWall(this, pos + dirOff));

        if (world->isOccupied(this, pos + dirOff))
            bump(dirOff);
        else
            move(dirOff);
        
        moveTime = sf::seconds(.5f);

        world->endTurn(this);
    }

    Entity::update(dt);
}

// Naive line drawing
// Where x1, y1 is the slime pos
// and x2 y2 is the player pos
bool Slime::playerLos()
{
    auto playerPos = world->getPlayerPos();

    float dx = playerPos.x - pos.x;
    float dy = playerPos.y - pos.y;

    if (pos.x < playerPos.x)
    {
        for (auto x = pos.x; x <= playerPos.x; x += 1.f)
        {
            // std::cout << "Here" << "\n";
            float y = pos.y + dy * (x - pos.x) / dx;

            world->map(x, y).setID(1);
        }
    }
    else
    {
        for (auto x = pos.x; x >= playerPos.x; x -= 1.f)
        {
            // std::cout << "Here" << "\n";
            float y = pos.y + dy * (x - pos.x) / dx;

            world->map(x, y).setID(1);
        }
    }

    return true;
}