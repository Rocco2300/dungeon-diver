#include "Enemy.h"

#include "World.h"
#include "Constants.h"

Enemy::Enemy()
{
}

int Enemy::heuristic(sf::Vector2i curr, sf::Vector2i end)
{
    int a = curr.x - end.x;
    int b = curr.y - end.y;
    return std::abs(a) + std::abs(b);
}

sf::Vector2i Enemy::getLowestScore()
{
    int min = 1000000;
    auto minIt = openSet.begin();

    for (auto it = openSet.begin(); it != openSet.end(); ++it)
    {
        if (fScore[*it] < min)
        {
            min = fScore[*it];
            minIt = it;
        }
    }

    return *minIt;
}

void Enemy::aStar()
{
    openSet.insert(this->pos);

    gScore[this->pos] = 0;
    fScore[this->pos] = heuristic(this->pos, world->getPlayerPos());

    while (!openSet.empty())
    {
        // auto current = 
    }
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

    int x = pos.x;
    int y = pos.y;

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