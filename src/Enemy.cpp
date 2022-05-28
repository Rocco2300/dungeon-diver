#include "Enemy.h"

#include <iostream>
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
    // std::cout << current.x << " " << current.y << std::endl;

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
        std::cout << current.x << " " << current.y << " \n";

        if (current == world->getPlayerPos())
        {
            std::cout << "huawa" << "\n";
            return reconstructPath(cameFrom, current);
        }

        openSet.erase(current);

        // Go through all the neighbours
        for (int i = 0; i < 4; i++)
        {
            auto neighbour = sf::Vector2i(current.x + dirX[i], current.y + dirY[i]);

            // if is wall
            if (world->isWall(nullptr, neighbour))
                continue; 

            auto tentGScore = gScore[current] + 1;
            auto found = gScore.find(neighbour) != gScore.end();
            if (found && tentGScore < gScore[neighbour])
            {
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentGScore;
                fScore[neighbour] = tentGScore + distance(neighbour, world->getPlayerPos());

                if (openSet.find(neighbour) == openSet.end())
                {
                    openSet.insert(neighbour);
                }
            }
            else if (!found)
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