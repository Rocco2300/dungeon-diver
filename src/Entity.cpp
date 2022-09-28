
#include "Entity.h"

#include <cmath>
#include <iostream>

#include "AssetManager.h"
#include "Lerp.h"
#include "World.h"

Entity::Entity()
{
    t     = 1.f;
    flip  = 1.f;
    frame = 0.f;

    pos.x = 0.f;
    pos.y = 0.f;

    turns = 1;
    dead  = false;

    const std::string path = std::string(PROJ_PATH) + "shader/shader.frag";
    if (!shader.loadFromFile(path, sf::Shader::Fragment))
        std::cerr << "Error loading shader.";

    tDmg = 0.f;
    shader.setUniform("percent", tDmg);
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    shader.setUniform("flashColor", sf::Glsl::Vec4(1, 1, 1, 1));
}

void Entity::setWorld(World& world) { this->world = &world; }

int Entity::getHp() { return hp; }

int Entity::getDamage() { return damage; }

int Entity::turnsLeft() { return turns; }

bool Entity::isDead() { return dead; }

void Entity::setHP(int hp) { this->hp = hp; }

void Entity::decrementTurns() { turns--; }

void Entity::setDamage(int damage) { this->damage = damage; }

void Entity::setSprite(std::string path, sf::Vector2i size)
{
    sprite.create(AssetManager::getTexture(path), size);
}

void Entity::takeDamage(int damageAmount)
{
    tDmg = 1.f;
    hp -= damageAmount;

    if (hp <= 0)
        dead = true;
}

void Entity::setPosition(sf::Vector2i pos) { this->pos = pos; }

void Entity::move(sf::Vector2i o)
{
    if (t != 1)
        return;

    pos += o;

    offS.x = -o.x * 8;
    offS.y = -o.y * 8;

    off = offS;

    t = 0;

    if (o.x != 0)
    {
        flip = o.x;
        clamp(flip, -1.f, 1.f);
    }

    animation = std::bind(&Entity::animateMove, this);
}

void Entity::bump(sf::Vector2i o)
{
    if (t != 1)
        return;

    offS.x = o.x * 8;
    offS.y = o.y * 8;

    off = offS;

    t = 0;

    if (o.x != 0)
    {
        flip = o.x;
        clamp(flip, -1.f, 1.f);
    }

    animation = std::bind(&Entity::animateBump, this);
}

void Entity::update(sf::Time dt)
{
    shader.setUniform("percent", tDmg);

    if (tDmg != 0.f)
    {
        tDmg -= 0.08f;

        if (tDmg < 0.f)
            tDmg = 0.f;
    }

    if (dead)
        return;

    frame += dt.asSeconds() * 5;

    sprite.setSpriteIndex((int) std::floor(frame) % 3);

    if (t != 1)
    {
        animate(dt.asSeconds() * 8);
    }
}

bool Entity::notMoving() { return (t == 1); }

sf::Vector2i Entity::getPosition() { return pos; }

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (dead)
        return;

    sf::Transform transform;
    transform.translate(pos.x * 8 + off.x, pos.y * 8 + off.y);
    transform.scale({flip, 1.f}, {4.f, 4.f});
    states.transform = transform;
    states.shader    = &shader;

    target.draw(sprite, states);
}

void Entity::endTurn()
{
    world->endTurn(this);

    if (turns == 0)
        turns = 1;
}

void Entity::animate(float animationSpeed)
{
    t = std::min(t + animationSpeed, 1.f);

    animation();
}

void Entity::animateMove()
{
    off.x = offS.x * (1 - t);
    off.y = offS.y * (1 - t);
}

void Entity::animateBump()
{
    if (t < 0.5f)
    {
        off.x = offS.x * t;
        off.y = offS.y * t;
    }
    else
    {
        off.x = offS.x * (1 - t);
        off.y = offS.y * (1 - t);
    }
}