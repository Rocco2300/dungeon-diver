#include "Game.h"

#include <iostream>
#include <fstream>

Game::Game()
{
    srand(time(NULL));

    clock.restart();

    window.create(sf::VideoMode(size * scale, size * scale), "Dungeon Diver");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    if (!texture.create(size, size))
        std::cerr << "Error creating render texture!\n";

    tileset.create("img/tiles.png", {8, 8});

    world.create(tileset);
}

void Game::run()
{
    while (window.isOpen())
    {
        dt = clock.restart();

        pollEvents();
        update(dt);
        draw();
    }
}

// void Game::handleInput(sf::Keyboard::Key key)
// {
//     auto it = keyMap.find(key);
            
//     if (it != keyMap.end())
//     {
//         auto idx = keyMap[key];

//         moveBuf.push_back({dirX[idx], dirY[idx]});
//     }
// }

void Game::pollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            world.keyPressed(event.key.code);
            // handleInput(event.key.code);
        }
    }
}

bool isInBounds(sf::Vector2i dest)
{
    return dest.x >= 0 && dest.x <= 16 && dest.y >= 0 && dest.y <= 16;
}

void Game::update(sf::Time dt)
{
    // if (!moveBuf.empty() && player.notMoving())
    // {
    //     auto mov = moveBuf.front();
    //     moveBuf.erase(moveBuf.begin());

    //     auto pos = player.getPosition();
        
    //     sf::Vector2i dest(mov.x + pos.x, mov.y + pos.y);

    //     if (map(dest).isWalkable())
    //         player.move({mov.x, mov.y});
    //     else
    //     {
    //         player.bump({mov.x, mov.y});

    //         if (map(dest).isInteractable())
    //         {
    //             const auto ID = map(dest).getID();

    //             map(dest).setInteractable(false);

    //             if (ID == 7 || ID == 8)
    //             {
    //                 map(dest).setID(1);
    //                 map(dest).setWalkable(true);
    //             }
    //             else if (ID == 3 || ID == 5)
    //                 map(dest).setID(ID+1);
    //         }
    //     }
    // }

    
    // player.update(dt);
    world.update(dt);
}

void Game::draw()
{
    texture.clear();
    texture.draw(world);
    // texture.draw(map);
    // texture.draw(player);
    texture.display();

    sf::Sprite spr;
    spr.setTexture(texture.getTexture());
    spr.setScale({scale, scale});

    window.clear();
    window.draw(spr);
    window.display();
}