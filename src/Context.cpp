#include "Context.h"

Context::Context()
{
    clock.restart();

    window.create(sf::VideoMode(size * scale, size * scale), "Dungeon Diver");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    if (!texture.create(size, size)) 
        std::cerr << "Error creating render texture!\n";

    game = new Game(*this);
}

void Context::run()
{
    while (window.isOpen())
    {
        dt = clock.restart();

        pollEvents();
        game->update(dt);
        draw();
    }
}

void Context::pollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        game->handleEvent(event);
    }
}

void Context::draw()
{
    texture.clear();
    game->draw();
    texture.display();

    sf::Sprite spr;
    spr.setTexture(texture.getTexture());
    spr.setScale({scale, scale});

    window.clear();
    window.draw(spr);
    window.display();
}