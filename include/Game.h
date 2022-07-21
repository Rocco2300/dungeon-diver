#pragma once

#include "World.h"

class Game : public sf::Drawable
{
private:
    World world;
    Tileset tileset;

public:
    Game() = default;
    Game(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

