#include "Enemy.h"

#include "Constants.h"
#include "World.h"
#include <iostream>

Enemy::Enemy()
{
    state    = AIState::Idle;
    moveTime = sf::seconds(.5f);
}

AIState Enemy::getState() { return state; }

void Enemy::setWorld(World& world)
{
    this->world = &world;
    aStar.setWorld(this->world);
}

void Enemy::handleState()
{
    switch (state)
    {
    case AIState::Idle:
        idle();
        break;
    case AIState::Chase:
        if (moveTime.asSeconds() <= 0)
            chase();
        break;
    case AIState::Investigate:
        if (moveTime.asSeconds() <= 0)
            investigate();
        break;
    }
}

void Enemy::idle()
{
    if (playerLos())
    {
        state = AIState::Chase;
        return;
    }

    endTurn();
}

void Enemy::chase()
{
    if (!playerLos())
    {
        state = AIState::Investigate;
        return;
    }

    playerPos = world->getPlayerPos();

    auto path = aStar.findPath(pos, playerPos);

    // If the path is blocked, go up to the enemy to still chase
    if (path.empty())
    {
        path = aStar.findPath(pos, playerPos, true);
    }

    if (!path.empty() && distToPlayer() > 1)
    {
        auto nextPos = path.back();
        auto dirOff  = sf::Vector2i(nextPos - pos);
        path.pop_back();

        if (!world->isOccupied(nextPos))
            move(dirOff);
    }
    else if (distToPlayer() == 1)
    {
        auto dirOff = sf::Vector2i(playerPos - pos);

        if (world->isOccupied(pos + dirOff))
        {
            bump(dirOff);
            world->attack(this, pos + dirOff);
        }
    }

    endTurn();
}

void Enemy::investigate()
{
    auto path = aStar.findPath(this->pos, playerPos, true);

    if (playerLos())
    {
        state = AIState::Chase;
        return;
    }

    if (path.empty() && !playerLos())
    {
        state = AIState::Idle;
        return;
    }

    if (distToPlayer() > 1)
    {
        auto nextPos = path.back();
        auto dirOff  = sf::Vector2i(nextPos - this->pos);
        path.pop_back();

        if (!world->isOccupied(nextPos))
            move(dirOff);
    }

    endTurn();
}

void Enemy::update(sf::Time dt)
{
    if (world->canMove(this) && state != AIState::Idle)
        moveTime -= dt;

    if (world->canMove(this))
        handleState();

    Entity::update(dt);
}

void Enemy::endTurn()
{
    world->endTurn(this);
    moveTime = sf::seconds(.5f);
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
        if (world->isWall({static_cast<int>(x), static_cast<int>(y)}))
            return false;

        x += dx;
        y += dy;
        i++;
    }

    return true;
}