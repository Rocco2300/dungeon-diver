#include <iostream>
#include "Player.h"

std::map<sf::Keyboard::Key, int> keyMap = 
{
    { sf::Keyboard::W, 0 },
    { sf::Keyboard::D, 1 },
    { sf::Keyboard::S, 2 },
    { sf::Keyboard::A, 3 },
};

int main()
{
    float scale = 3.f;
    int size = 8 * 16;
    sf::RenderWindow window(sf::VideoMode(size * scale, size * scale), "SFML works!");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::RenderTexture tex;
    if (!tex.create(size, size))
        std::cerr << "Error creating render texture!\n";

    Player player({.5f, .5f});

    sf::Time dt;
    sf::Clock clk;
    while (window.isOpen())
    {
        dt = clk.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                auto it = keyMap.find(event.key.code);
                
                if (it != keyMap.end())
                {
                    auto idx = keyMap[event.key.code];
                    player.move(idx);
                }
            }
        }

        player.update(dt);

        tex.clear(sf::Color(62, 35, 44, 255));
        tex.draw(player);
        tex.display();

        sf::Sprite spr;
        spr.setTexture(tex.getTexture());
        spr.setScale({scale, scale});

        window.clear();
        window.draw(spr);
        window.display();
    }

    return 0;
}