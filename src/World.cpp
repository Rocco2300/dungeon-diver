#include "World.h"

#include <iostream>

#include "SoundManager.h"

void World::create(Map& map, Player& player, std::vector<Entity*>& entities)
{
    gameOver  = false;
    nextLevel = false;

    this->map      = &map;
    this->player   = &player;
    this->entities = &entities;

    this->playerTurn = true;

    moveTime = sf::seconds(.3f);
}


int World::getPlayerLife() { return player->getHp(); }

bool World::isGameOver() { return gameOver; }

bool World::goNextLevel() { return nextLevel; }

bool World::isPlayerTurn() { return playerTurn; }

bool World::canMove(Entity* caller) { return toMove.count(caller); }

bool World::isWall(Entity* caller, sf::Vector2i pos)
{
    if (!isInBounds(pos)) return true;

    return !map->at(pos).isWalkable();
}

bool World::isOccupied(Entity* caller, sf::Vector2i pos)
{
    for (int i = entities->size() - 1; i >= 0; i--)
    {
        if (pos == entities->at(i)->getPosition()) { return true; }
    }
    return false;
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
    if (!isInBounds(pos)) return;

    if (caller == player)
    {
        auto interactableTile = dynamic_cast<InteractableTile*>(&map->at(pos));

        if (interactableTile)
        {
            interactableTile->onInteract();

            auto exitTile = dynamic_cast<ExitStairsTile*>(interactableTile);
            if (exitTile) nextLevel = true;
        }
    }
}

Player& World::getPlayerRef() { return *player; }

sf::Vector2i World::getPlayerPos() { return player->getPosition(); }

std::vector<Entity*>& World::getEntities() { return *entities; }

void World::endTurn(Entity* entity)
{
    if (entity == player)
    {
        playerTurn = false;

        toMove.clear();
        for (size_t i = 0; i < entities->size(); i++)
        {
            if (entities->at(i) != player) toMove.insert(entities->at(i));
        }
        // DEBUG
        // for (int i = 0; i < 16; i++)
        // {
        //     for (int j = 0; j < 16; j++)
        //     {
        //         map(i, j).setDebug(false);
        //     }
        // }
    }
    else
    {
        if (toMove.count(entity)) toMove.erase(entity);

        if (toMove.empty()) playerTurn = true;
    }
}

void World::setGameOver(bool value) { gameOver = value; }

void World::setNextLevel(bool value) { nextLevel = value; }

void World::keyPressed(sf::Keyboard::Key key) { player->onKeyPressed(key); }

void World::update(sf::Time dt)
{
    if (gameOver) return;

    if (entities->size() < 2) playerTurn = true;

    player->update(dt);
    for (size_t i = 0; i < entities->size(); i++)
    {
        auto enemy = dynamic_cast<Enemy*>(entities->at(i));
        if (enemy) { enemy->update(dt); }
    }

    // Remove sounds that finished playing
    SoundManager::cleanSounds();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*map, states);

    for (size_t i = 0; i < entities->size(); i++)
    {
        target.draw(*entities->at(i), states);
    }
}

bool World::isInBounds(sf::Vector2i pos)
{
    return (pos.x >= 0 && pos.x < 16 && pos.y >= 0 && pos.y < 16);
}