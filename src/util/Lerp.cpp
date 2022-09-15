#include "Lerp.h"

#include <cmath>

float lerp(float a, float b, float t) { return a + (b - a) * t; }

sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t)
{
    return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
}

void clamp(float& num, float a, float b)
{
    if (num < a)
        num = a;
    else if (num > b)
        num = b;
}

float distance(sf::Vector2f a, sf::Vector2f b)
{
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}