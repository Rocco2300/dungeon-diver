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
        Path path;
        auto playerPos = world->getPlayerPos();

        if (playerLos())
        {
            path = aStar(this->pos, playerPos);

            // @Debugging
            // for (int i = 0; i < path.size(); i++)
            // {
            //     world->map(path[i]).setDebug(true);
            //     world->map(path[i]).setDebugRect(sf::Color::Green, 120);
            // }
        }

        if (!path.empty() && distance(this->pos, playerPos) > 1)
        {
            auto nextPos = path.front();
            auto dirOff = sf::Vector2i(nextPos - this->pos);
            path.erase(path.begin());

            move(dirOff);
        }
        else if (distance(this->pos, world->getPlayerPos()) == 1)
        {
            auto dirOff = sf::Vector2i(playerPos - this->pos);

            bump(dirOff);
        }

        moveTime = sf::seconds(.5f);

        world->endTurn(this);
    }

    Entity::update(dt);
}
