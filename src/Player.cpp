#include "Player.h"

#include <iostream>
#include <cmath>

Player::Player()
{
    sprite.create("img/player.png", {8, 8});
}

void Player::update(sf::Time dt)
{
    Entity::update(dt);
}
