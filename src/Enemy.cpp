#include "Enemy.h"

#include "World.h"
#include "Constants.h"

Enemy::Enemy()
{
}

int Enemy::distance(sf::Vector2i curr, sf::Vector2i end)
{
    int a = curr.x - end.x;
    int b = curr.y - end.y;
    return std::abs(a) + std::abs(b);
}

sf::Vector2i Enemy::getLowestScore(TileHashSet& openSet, ScoreHashMap& fScore)
{
    int min = 2'000'000'000;
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

Enemy::Path Enemy::reconstructPath(PathHashMap cameFrom, sf::Vector2i current)
{
    Path totalPath;

    while (cameFrom.find(current) != cameFrom.end())
    {
        current = cameFrom[current];
        totalPath.push_back(current);
    }

    return totalPath;
}

Enemy::Path Enemy::aStar()
{
    TileHashSet openSet;
    openSet.insert(this->pos);

    PathHashMap cameFrom;

    ScoreHashMap fScore;
    ScoreHashMap gScore;

    gScore[this->pos] = 0;
    fScore[this->pos] = distance(this->pos, world->getPlayerPos());

    while (!openSet.empty())
    {
        auto current = getLowestScore(openSet, fScore);

        if (current == world->getPlayerPos())
            return reconstructPath(cameFrom, current);

        openSet.erase(current);

        // Go through all the neighbours
        for (int i = 0; i < 4; i++)
        {
            // if is wall
            if (world->isWall(nullptr, {dirX[i], dirY[i]}))
                continue; 
            
            auto neighbour = sf::Vector2i(dirX[i], dirY[i]);

            auto tentGScore = gScore[current] + 1;

            if (tentGScore < gScore[neighbour])
            {
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentGScore;
                fScore[neighbour] = tentGScore + distance(neighbour, world->getPlayerPos());

                if (openSet.find(neighbour) == openSet.end())
                {
                    openSet.insert(neighbour);
                }
            }
        }
    }

    return Path();
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