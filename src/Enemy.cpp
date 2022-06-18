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
    if (!world->isPlayerTurn() && state != AIState::Idle)
        moveTime -= dt;

    if (!world->isPlayerTurn() && state == AIState::Idle)
    {
        if (!world->isPlayerTurn() && playerLos())
            state = AIState::Chase;
    }

    if (!world->isPlayerTurn() && state == AIState::Chase && moveTime.asSeconds() <= 0)
    {
        if (!playerLos())
        {
            state = AIState::Investigate;
        }

        if (playerLos())
            playerPos = world->getPlayerPos();

        auto path  = aStar.findPath(this->pos, playerPos);
        
        if (path.empty() && !playerLos())
            state = AIState::Idle;

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

    if (!world->isPlayerTurn() && state == AIState::Investigate && moveTime.asSeconds() <= 0)
    {
        if (playerLos())
        {
            state = AIState::Chase;
            playerPos = world->getPlayerPos();
        }

        auto path  = aStar.findPath(this->pos, playerPos);
        
        if (path.empty() && !playerLos())
            state = AIState::Idle;

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

    if (state == AIState::Idle)
        world->endTurn(this);

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
        // DEBUG
        // world->map((int)x, (int)y).setDebug(true);
        // world->map((int)x, (int)y).setDebugRect(sf::Color::Green, 150);

        if (world->isWall(nullptr, {static_cast<int>(x), static_cast<int>(y)}))
            return false;

        x += dx;
        y += dy;
        i ++;
    }

    return true;
}