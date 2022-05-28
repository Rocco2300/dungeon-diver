#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Entity.h"

class World;



class Enemy : public Entity
{
private:
    struct VectorHash
    {
        size_t operator()(const sf::Vector2i& op) const
        {
            auto hash1 = std::hash<std::string>{}(std::to_string(op.x));
            auto hash2 = std::hash<std::string>{}(std::to_string(op.y));

            return hash1 ^ hash2;
        }
    };

protected:
    sf::Time moveTime;

public:
    Enemy();

    virtual ~Enemy() = default;

protected:
    bool playerLos();

public:
    int distance(sf::Vector2i curr, sf::Vector2i end);
    sf::Vector2i getLowestScore(std::unordered_set<sf::Vector2i, VectorHash>& openSet,
        std::unordered_map<sf::Vector2i, int, VectorHash>& fScore);
    void aStar();
    void reconstructPath();
};

