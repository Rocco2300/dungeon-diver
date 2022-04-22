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

std::vector<std::vector<int>> loadMap(const char* path)
{
    std::vector<std::vector<int>> map;
    std::ifstream in(path);

    int x;
    for (int i = 0; i < 16; i++)
    {
        std::vector<int> temp;
        for (int j = 0; j < 16; j++)
        {
            in >> x;

            temp.push_back(x);
        }
        map.push_back(temp);
    }

    in.close();
    return map;
}

int main()
{
    float scale = 4.f;
    int size = 8 * 16;
    sf::RenderWindow window(sf::VideoMode(size * scale, size * scale), "SFML works!");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::RenderTexture tex;
    if (!tex.create(size, size))
        std::cerr << "Error creating render texture!\n";

    Player player({.5f, .5f});

    sf::Texture tileTex;
    if(!tileTex.loadFromFile("img/tiles.png"))
        std::cerr << "error\n";

    sf::Sprite spr;
    spr.setTexture(tileTex);
    spr.setTextureRect({{0, 0}, {8, 8}});

    std::vector<std::vector<int>> map = loadMap("map.txt");

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
            for (size_t j = 0; j < map[i].size(); j++)
            {
                spr.setTextureRect({{map[i][j] * 8.f, 0}, {8, 8}});
                spr.setPosition(j * 8.f, i * 8.f);
                tex.draw(spr);
            }
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