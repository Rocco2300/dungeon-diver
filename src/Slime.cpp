#include "Slime.h"

#include <random>

Slime::Slime()
{
    sprite.create("img/slime.png", {8, 8});
}

void Slime::update(sf::Time dt)
{
    Entity::update(dt);
}