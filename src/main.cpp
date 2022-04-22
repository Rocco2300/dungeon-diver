#include <iostream>
#include <fstream>
#include "Player.h"

std::map<sf::Keyboard::Key, int> keyMap = 
{
    { sf::Keyboard::W, 0 },
    { sf::Keyboard::D, 1 },
    { sf::Keyboard::S, 2 },
    { sf::Keyboard::A, 3 },
};

std::vector<sf::Sprite> loadMap(const char* path, sf::Texture& tex)
{
    std::vector<sf::Sprite> map;
    std::ifstream in(path);

    if(!tex.loadFromFile("img/brick.png"))
        std::cerr << "Error loading brick texture!\n";

    int x;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            in >> x;

            if (x != 0)
            {
                sf::Sprite spr;
                spr.setTexture(tex);
                spr.setPosition(j * 8.f, i * 8.f);
                map.push_back(spr);
            }
        }
    }

    in.close();
    return map;
}

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

    sf::Texture brickTex;
    std::vector<sf::Sprite> map = loadMap("map.txt", brickTex);

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
        for (size_t i = 0; i < map.size(); i++)
        {
            tex.draw(map[i]);
        }

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