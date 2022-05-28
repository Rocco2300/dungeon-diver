#include "Enemy.h"

#include <cmath>
#include "World.h"
#include "Constants.h"

Enemy::Enemy()
{
}

int Enemy::heuristic(sf::Vector2f curr, sf::Vector2f end)
{
    int a = curr.x - end.x;
    int b = curr.y - end.y;
    return std::abs(a) + std::abs(b);
}

bool Enemy::playerLos()
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