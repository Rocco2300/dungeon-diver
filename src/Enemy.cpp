#include "Enemy.h"

#include <iostream>
#include "World.h"
#include "Constants.h"

Enemy::Enemy()
{
    state = AIState::Idle;
    moveTime = sf::seconds(.5f);
}

AIState Enemy::getState()
{
    return state;
}

void Enemy::setWorld(World& world)
{
    this->world = &world;
    aStar.setWorld(this->world);
}

void Enemy::update(sf::Time dt)
{
    if (playerLos())    
        state = AIState::Chase;
    else 
        state = AIState::Idle;

    if (!world->isPlayerTurn())
        moveTime -= dt;

    if (!world->isPlayerTurn() && moveTime.asSeconds() <= 0)
    {
        Path path;
        auto playerPos = world->getPlayerPos();

        if (state == AIState::Chase)
        {
            path  = aStar.findPath(this->pos, playerPos);

            // @Debugging
            // world->map(path[path.size()-1]).setDebug(true);
            // world->map(path[path.size()-1]).setDebugRect(sf::Color::Red, 120);
            // for (int i = 0; i < path.size()-1; i++)
            // {
            //     world->map(path[i]).setDebug(true);
            //     world->map(path[i]).setDebugRect(sf::Color::Green, 120);
            // }
        }

        if (!path.empty() && distToPlayer() > 1)
        {
            auto nextPos = path.back();
            auto dirOff = sf::Vector2i(nextPos - this->pos);
            path.pop_back();

            move(dirOff);
        }
        else if (distToPlayer() == 1)
        {
            auto dirOff = sf::Vector2i(playerPos - this->pos);

            bump(dirOff);
        }

        moveTime = sf::seconds(.5f);

        world->endTurn(this);
    }

    Entity::update(dt);
}

int Enemy::distToPlayer()
{
    int a = pos.x - world->getPlayerPos().x;
    int b = pos.y - world->getPlayerPos().y;
    return std::abs(a) + std::abs(b);
}

bool Enemy::playerLos()
{
    bool res = true;

    auto playerPos = world->getPlayerPos();
    // std::cout << playerPos.x << " " << playerPos.y << '\n';

    float dx = playerPos.x - pos.x;
    float dy = playerPos.y - pos.y;

    float step;
    if (std::abs(dx) >= std::abs(dy))
        step = std::abs(dx);
    else
        step = std::abs(dy);

    dx /= step;
    dy /= step;

    float x = pos.x;
    float y = pos.y;

    int i = 1;
    while (i <= step)
    {   
        if (world->isWall(nullptr, {x, y}))
            res = false;

        x += dx;
        y += dy;
        i ++;
    }

    return res;
}