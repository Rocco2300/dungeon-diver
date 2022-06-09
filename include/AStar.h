#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "SFML/Graphics.hpp"

class World;

using Path = std::vector<sf::Vector2i>;

class AStar
{
private:
    World* world;
    std::vector<int>* colMap;

    struct VectorHash
    {
        size_t operator()(const sf::Vector2i& op) const
        {
            auto hash1 = std::hash<std::string>{}(std::to_string(op.x));
            auto hash2 = std::hash<std::string>{}(std::to_string(op.y));

            return hash1 ^ hash2;
        }
    };

    using ScoreHashMap = std::unordered_map<sf::Vector2i, int, VectorHash>;
    using TileHashSet = std::unordered_set<sf::Vector2i, VectorHash>; 
    using PathHashMap = std::unordered_map<sf::Vector2i, sf::Vector2i, VectorHash>;
public:
    AStar();
    AStar(World* world);
    AStar(std::vector<int>& colMap);

    void setWorld(World* world);
    void setColMap(std::vector<int>& colMap);

    Path findPath(sf::Vector2i start, sf::Vector2i end);
private:
    int distance(sf::Vector2i curr, sf::Vector2i end);
    Path reconstructPath(PathHashMap cameFrom, sf::Vector2i current);
    sf::Vector2i getLowestScore(TileHashSet& openSet, ScoreHashMap& fScore);

    Path colMapFindPath(sf::Vector2i start, sf::Vector2i end);
    Path worldMapFindPath(sf::Vector2i start, sf::Vector2i end);
};

