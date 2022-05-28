#include "Slime.h"

#include "World.h"
#include "Constants.h"

#include <random>
#include <iostream>

Slime::Slime()
{
    hp = 1;

    moveTime = sf::seconds(.5f);

    sprite.create("img/slime.png", {8, 8});
}

void Slime::update(sf::Time dt)
{
    if (!world->isPlayerTurn())
        moveTime -= dt;

    if (!world->isPlayerTurn() && moveTime.asSeconds() <= 0)
    {
        if (playerLos())
        {
            auto path = aStar();
            for (int i = 0; i < 16; i++)
            {
                for (int j = 0; j < 16; j++)
                {
                    if (world->map(i, j).getID() == 1)
                        world->map(i, j).setID(0);
                }
            }

            for (int i = 0; i < path.size(); i++)
            {
                world->map(path[i]).setID(1);
            }
        }

        int randDir;
        sf::Vector2i dirOff;

        do 
        {
            randDir = rand() % 4;

            dirOff = sf::Vector2i(dirX[randDir], dirY[randDir]);
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
