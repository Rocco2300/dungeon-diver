#pragma once

#include <SFML/Graphics.hpp>

extern float        lerp(float a, float b, float t);
extern sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t);

extern void  clamp(float& num, float a, float b);
extern float distance(sf::Vector2f a, sf::Vector2f b);
