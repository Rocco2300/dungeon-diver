#include "AStar.h"

#include <iostream>

#include "World.h"
#include "Constants.h"

AStar::AStar()
{
    world  = nullptr;
    colMap = nullptr;
}

AStar::AStar(World* world)
{
    this->world  = world;
    this->colMap = nullptr;
}

AStar::AStar(std::vector<int>& colMap)
{
    this->world  = nullptr;
    this->colMap = &colMap;
}

void AStar::setWorld(World* world)
{
    this->world = world;
}

void AStar::setColMap(std::vector<int>& colMap)
{
    this->colMap = &colMap;
}

int AStar::distance(sf::Vector2i curr, sf::Vector2i end)
{
    int a = curr.x - end.x;
    int b = curr.y - end.y;
    return std::abs(a) + std::abs(b);
}

sf::Vector2i AStar::getLowestScore(TileHashSet& openSet, ScoreHashMap& fScore)
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

Path AStar::reconstructPath(PathHashMap cameFrom, sf::Vector2i current)
{
    Path totalPath;

    while (cameFrom.find(current) != cameFrom.end())
    {
        current = cameFrom[current];
        totalPath.push_back(current);
    }

    totalPath.pop_back();
    return totalPath;
}

Path AStar::findPath(sf::Vector2i start, sf::Vector2i end)
{
    Path res{};

    if (world)
        res = worldMapFindPath(start, end);
    else if (colMap)
        res = colMapFindPath(start, end);

    return res;
}


Path AStar::colMapFindPath(sf::Vector2i start, sf::Vector2i end)
{
    TileHashSet openSet;
    openSet.insert(start);

    PathHashMap cameFrom;

    ScoreHashMap fScore;
    ScoreHashMap gScore;

    gScore[start] = 0;
    fScore[start] = distance(start, end);

    while (!openSet.empty())
    {
        auto current = getLowestScore(openSet, fScore);

        if (current == end)
            return reconstructPath(cameFrom, current);

        openSet.erase(current);

        // Go through all the neighbours
        for (int i = 0; i < 4; i++)
        {
            auto neighbour = sf::Vector2i(current.x + dirX[i], current.y + dirY[i]);

            // if is wall
            bool inBounds = (neighbour.x >= 0 && neighbour.x < 16 && neighbour.y >= 0 && neighbour.y < 16);
            if (((inBounds && colMap->at(neighbour.y * 16 + neighbour.x) == 1) || !inBounds))
                continue; 

            auto tentGScore = gScore[current] + 1;
            auto found = gScore.find(neighbour) != gScore.end();
            if ((found && tentGScore < gScore[neighbour]) || !found)
            {
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentGScore;
                fScore[neighbour] = tentGScore + distance(neighbour, end);

                if (openSet.find(neighbour) == openSet.end())
                {
                    openSet.insert(neighbour);
                }
            }
        }
    }

    return Path();
}

Path AStar::worldMapFindPath(sf::Vector2i start, sf::Vector2i end)
{
    TileHashSet openSet;
    openSet.insert(start);

    PathHashMap cameFrom;

    ScoreHashMap fScore;
    ScoreHashMap gScore;

    gScore[start] = 0;
    fScore[start] = distance(start, end);

    while (!openSet.empty())
    {
        auto current = getLowestScore(openSet, fScore);

        if (current == end)
            return reconstructPath(cameFrom, current);

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
            if ((found && tentGScore < gScore[neighbour]) || !found)
            {
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentGScore;
                fScore[neighbour] = tentGScore + distance(neighbour, end);

                if (openSet.find(neighbour) == openSet.end())
                {
                    openSet.insert(neighbour);
                }
            }
        }
    }

    return Path();
}