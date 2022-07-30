#include "Application.h"

Application::Application() : scale{4.f}, size{8 * 16}
{
    clock.restart();

    window.create(sf::VideoMode(size * scale, size * scale), "Dungeon Diver");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    if (!texture.create(size, size)) 
        std::cerr << "Error creating render texture!\n";

    // No non-trivial copy constructor
    // and unique_ptr member, have to heap alloc
    stateStack = new StateStack(texture);
    registerStates();
    stateStack->pushState(StateID::MainMenu);
}

void Application::run()
{
    while (window.isOpen())
    {
        dt = clock.restart();
        

        pollEvents();
        update(dt);
        draw();
        
        if (stateStack->isEmpty())
            window.close();
    }
}

void Application::pollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        stateStack->handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    stateStack->update(dt);
}

void Application::draw()
{
    texture.clear();
    stateStack->draw();
    texture.display();

    sf::Sprite spr;
    spr.setTexture(texture.getTexture());
    spr.setScale({scale, scale});

    window.clear();
    window.draw(spr);
    window.display();
}

void Application::registerStates()
{
    stateStack->registerState<MainMenu>(StateID::MainMenu);
    stateStack->registerState<Game>(StateID::Game);
}