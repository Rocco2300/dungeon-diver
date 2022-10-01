#include "World.h"

#include <iostream>

#include "SoundManager.h"

void World::create(Map& map, Player& player, std::vector<Entity*>& entities)
{
    toMove = 0;

    gameOver  = false;
    nextLevel = false;

    this->map      = &map;
    this->player   = &player;
    this->entities = &entities;

    moveTime = sf::seconds(.3f);
}


int World::getPlayerLife() { return player->getHp(); }

bool World::isGameOver() { return gameOver; }

bool World::goNextLevel() { return nextLevel; }

bool World::canMove(Entity* caller)
{
    auto it = std::find(entities->begin(), entities->end(), caller);

    if (it == entities->end())
        return false;

    auto index = std::distance(entities->begin(), it);
    if (caller == *it && index == toMove)
        return true;

    return false;
}

bool World::isWall(sf::Vector2i pos)
{
    if (!isInBounds(pos))
        return true;

    return !map->at(pos).isWalkable();
}

bool World::isOccupied(sf::Vector2i pos)
{
    for (int i = entities->size() - 1; i >= 0; i--)
    {
        if (pos == entities->at(i)->getPosition())
        {
            return true;
        }
    }
    return false;
}

bool World::isInteractable(sf::Vector2i pos)
{
    if (!isInBounds(pos))
        return false;

    return dynamic_cast<InteractableTile*>(&map->at(pos));
}

void World::attack(Entity* caller, sf::Vector2i pos)
{
    for (int i = entities->size() - 1; i >= 0; i--)
    {
        auto entity = entities->at(i);

        if (pos == entity->getPosition())
        {
            entity->takeDamage(caller->getDamage());

            SoundManager::playSound("hit1");

            if (entities->at(i)->isDead())
            {
                if (entities->at(i) == player)
                {
                    gameOver = true;
                    return;
                }
                delete entities->at(i);
                entities->erase(entities->begin() + i);
            }
        }
    }
}

void World::interact(Entity* caller, sf::Vector2i pos)
{
    if (!isInBounds(pos))
        return;

    if (caller == player)
    {
        auto interactableTile = dynamic_cast<InteractableTile*>(&map->at(pos));

        if (interactableTile)
        {
            interactableTile->onInteract();

            auto exitTile = dynamic_cast<ExitStairsTile*>(interactableTile);
            if (exitTile)
                nextLevel = true;
        }
    }
}

Player& World::getPlayerRef() { return *player; }

sf::Vector2i World::getPlayerPos() { return player->getPosition(); }

std::vector<Entity*>& World::getEntities() { return *entities; }

void World::endTurn(Entity* entity)
{
    auto it = std::find(entities->begin(), entities->end(), entity);

    if (it == entities->end())
        return;

    auto index = std::distance(entities->begin(), it);
    if (entity == *it && index == toMove)
    {
        entity->decrementTurns();

        if (entity->turnsLeft() == 0)
        {
            toMove = (toMove + 1) % entities->size();
        }
    }
}

void World::setGameOver(bool value) { gameOver = value; }

void World::setNextLevel(bool value) { nextLevel = value; }

void World::keyPressed(sf::Keyboard::Key key) { player->onKeyPressed(key); }

void World::update(sf::Time dt)
{
    if (gameOver)
        return;

    player->update(dt);
    for (auto& entity : *entities)
    {
        auto enemy = dynamic_cast<Enemy*>(entity);
        if (enemy)
        {
            enemy->update(dt);
        }
    }

    // Remove sounds that finished playing
    SoundManager::cleanSounds();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*map, states);

    for (auto& entity : *entities)
    {
        target.draw(*entity, states);
    }
}

bool World::isInBounds(sf::Vector2i pos)
{
    return (pos.x >= 0 && pos.x < 16 && pos.y >= 0 && pos.y < 16);
}