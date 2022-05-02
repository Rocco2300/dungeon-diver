#include "Slime.h"

#include "World.h"
#include <random>

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