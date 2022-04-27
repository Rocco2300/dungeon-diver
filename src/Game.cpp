#include "Game.h"

#include <iostream>
#include <fstream>

Game::Game()
{
    srand(time(NULL));
    slimeMovTime = sf::seconds(1.f);

    clock.restart();

    window.create(sf::VideoMode(size * scale, size * scale), "Dungeon Diver");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    if (!texture.create(size, size))
        std::cerr << "Error creating render texture!\n";

    tileset.create("img/tiles.png", {8, 8});

    map.setSize({16, 16});
    map.setTileset(tileset);
    map.loadMap("map.txt");
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

void Game::handleInput(sf::Keyboard::Key key)
{
    auto it = keyMap.find(key);
            
    if (it != keyMap.end())
    {
        auto idx = keyMap[key];

        moveBuf.push_back({dirX[idx], dirY[idx]});
    }
}

void Game::pollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            handleInput(event.key.code);
        }
    }
}

bool isInBounds(sf::Vector2i dest)
{
    return dest.x >= 0 && dest.x <= 16 && dest.y >= 0 && dest.y <= 16;
}

void Game::update(sf::Time dt)
{
    if (!moveBuf.empty() && player.notMoving())
    {
        auto mov = moveBuf.front();
        moveBuf.erase(moveBuf.begin());

        auto pos = player.getPosition();
        
        sf::Vector2i dest(mov.x + pos.x, mov.y + pos.y);

        if (map(dest).isWalkable())
            player.move({mov.x, mov.y});
        else
        {
            player.bump({mov.x, mov.y});

            if (map(dest).isInteractable())
            {
                const auto ID = map(dest).getID();

                map(dest).setInteractable(false);

                if (ID == 7 || ID == 8)
                {
                    map(dest).setID(1);
                    map(dest).setWalkable(true);
                }
                else if (ID == 3 || ID == 5)
                    map(dest).setID(ID+1);
            }
        }
    }

    slimeMovTime -= dt;

    if (slimeMovTime.asSeconds() <= 0.f)
    {  
        int randDir;
        sf::Vector2i dest;

        do 
        {
            randDir = rand() % 4;
            dest.x = dirX[randDir] + slime.getPosition().x;
            dest.y = dirY[randDir] + slime.getPosition().y;

        } while(!map(dest).isWalkable() || !isInBounds(dest));

        if (map(dest).isWalkable())
            slime.move({dirX[randDir], dirY[randDir]});

        slimeMovTime = sf::seconds(1.f);
    }
    
    player.update(dt);
    slime.update(dt);
}

void Game::draw()
{
    texture.clear();
    texture.draw(map);
    texture.draw(player);
    texture.draw(slime);
    texture.display();

    sf::Sprite spr;
    spr.setTexture(texture.getTexture());
    spr.setScale({scale, scale});

    window.clear();
    window.draw(spr);
    window.display();
}