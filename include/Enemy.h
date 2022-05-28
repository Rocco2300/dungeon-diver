#pragma once

#include <string>
#include <unordered_map>
#include "Entity.h"

class World;

struct MyHash
{
    size_t operator()(const sf::Vector2i& op) const
    {
        auto hash1 = std::hash<std::string>{}(std::to_string(op.x));
        auto hash2 = std::hash<std::string>{}(std::to_string(op.y));

        return hash1 ^ hash2;
    }
};

class Enemy : public Entity
{
protected:
    std::unordered_map<sf::Vector2i, int, MyHash> gScore;
    sf::Time moveTime;

public:
    Enemy();

    virtual ~Enemy() = default;

protected:
    bool playerLos();

public:
    int heuristic(sf::Vector2i curr, sf::Vector2i end);
    void aStar();
    void reconstructPath();
};

