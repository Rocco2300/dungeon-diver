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
        std::cout << x << std::endl;

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

bool Slime::playerLos()
{
    auto playerPos = world->getPlayerPos();

    float dx = playerPos.x - pos.x;
    float dy = playerPos.y - pos.y;

    float step;
    if (std::abs(dx) >= std::abs(dy))
        step = std::abs(dx);
    else
        step = std::abs(dy);

    dx /= step;
    dy /= step;

    float x = pos.x;
    float y = pos.y;

    int i = 1;
    while (i <= step)
    {   
        if (world->isWall(nullptr, {x, y}))
            return false;

        x += dx;
        y += dy;
        i ++;
    }

    return true;
}