#include <iostream>
#include <SFML/Graphics.hpp>

struct Player
{
    sf::RectangleShape spr;
    sf::Vector2f pos;
};

int dirX[4] = {0, 1, 0, -1};
int dirY[4] = {-1, 0, 1, 0};
std::map<sf::Keyboard::Key, int> keyMap = 
{
    { sf::Keyboard::W, 0 },
    { sf::Keyboard::D, 1 },
    { sf::Keyboard::S, 2 },
    { sf::Keyboard::A, 3 },
};
int main()
{
    sf::Clock clk;

    float scale = 3.f;
    int size = 8 * 16;
    sf::RenderWindow window(sf::VideoMode(size * scale, size * scale), "SFML works!");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    Player player;
    player.spr = sf::RectangleShape({8.f, 8.f});


    sf::RenderTexture tex;
    if (!tex.create(size, size))
        std::cerr << "Error creating render texture!\n";

    int x = 0;
    int y = 0;

    player.pos = sf::Vector2f(x, y);

    int offX = 0;
    int offY = 0;

    float t = 0;
    sf::Time dt = clk.restart();
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

                    x += dirX[idx];
                    y += dirY[idx];
                    offX = -dirX[idx] * 8;
                    offY = -dirY[idx] * 8;
                    t = 0;
                }
            }

            player.pos.x = x * 8;
            player.pos.y = y * 8;
        }

        // (x * 8 + offX, y * 8);
        player.spr.setPosition(player.pos.x + offX, player.pos.y + offY);

        t = std::min(t + 0.05f, 1.f);

        offX = offX * (1 - t);
        offY = offY * (1 - t);

        if(t == 1)
            t = 0;

        tex.clear();
        tex.draw(player.spr);
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