#pragma once

#include "World.h"

class Game : public sf::Drawable
{
private:
    sf::RenderWindow* window;

    World world;
    Tileset tileset;

public:
    Game() = default;
    Game(sf::RenderWindow& window);

    void pollEvents();
    void update(sf::Time dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

