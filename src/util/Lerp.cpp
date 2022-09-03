#include "Lerp.h"

inline float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

inline sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t)
{
    return {
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t
    };
}