#include "Game.h"

#include <memory>
#include <iostream>

#include "StateStack.h"
#include "AssetManager.h"

#include "ItemFactory.h"

Game::Game(StateStack& stateStack, Context context)
    : State(stateStack, context)
{
    tileset.create(AssetManager::getTexture("tiles"), {8, 8});
    world.create(map, player, entities);

    Context contxt = stateStack.getContext();
    contxt.world = &world;
    stateStack.setContext(contxt);

    initUI();

    gen.generateMap();
    auto stream = gen.getMapAsStream();
    auto playerPos = gen.getEntrance();

    map.setSize({16, 16});
    map.setTileset(this->tileset);
    map.loadMap(stream);
    
    player.setWorld(world);
    player.setPosition(playerPos);

    entities.push_back(&player);
    spawner.init(world);

    ItemFactory itemFact(player);
    itemFact.givePlayerItem();
    itemFact.givePlayerItem();

    std::vector<sf::Vector2i> openTiles;
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        if (map(x, y).isWalkable())
            openTiles.emplace_back(x, y);
    }

    for (int i = 0; i < 2; i++)
    {
        auto idx = rand() % openTiles.size();
        spawner.spawnEnemy({openTiles[idx].x, openTiles[idx].y});
        openTiles.erase(openTiles.begin() + idx);
    }
}

void Game::initUI()
{
    auto textLabel = std::make_shared<GUI::TextLabel>();
    textLabel->setSize({8, 8});
    textLabel->setAllignment(Allign::Center);
    textLabel->setPosition({0, 0});

    auto spriteLabel = std::make_shared<GUI::SpriteLabel>();
    spriteLabel->setSize({8, 8});
    spriteLabel->setSprite("gui_elements");
    spriteLabel->setSpriteRect({16, 0, 8, 8});
    spriteLabel->setPosition({6, 0});

    hpDisplay.setSize({16, 8});
    hpDisplay.setPosition({2, 2});
    hpDisplay.getBackgoundRef().setFillColor(sf::Color::Black);
    hpDisplay.getBackgoundRef().setOutlineColor(sf::Color::White);
    hpDisplay.getBackgoundRef().setOutlineThickness(1);
    hpDisplay.getBackgoundRef().setSize({16, 8});
    
    hpDisplay.pack(textLabel);
    hpDisplay.pack(spriteLabel);
}

bool Game::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            stateStack->popState();
            stateStack->pushState(StateID::MainMenu);
        }
        else if (event.key.code == sf::Keyboard::Tab)
        {
            stateStack->pushState(StateID::Inventory);
        }

        sf::Vector2i pos;
        std::stringstream stream;
        // @Debugging
        switch (event.key.code)
        {
        case sf::Keyboard::Comma:
            gen.printAreasArray();
            break;
        case sf::Keyboard::Period:
            gen.printWallsArray();
            break;
        case sf::Keyboard::Slash:
            gen.printSignatures();
            break;
        case sf::Keyboard::SemiColon:
            gen.printRoomMap();
            break;
        case sf::Keyboard::G:
            gen.generateMap();
            stream = gen.getMapAsStream();
            pos = gen.getEntrance();
            player.setPosition(pos);
            map.loadMap(stream);
            break;
        default:
            break;
        }

        world.keyPressed(event.key.code);
    }

    return false;
}

bool Game::update(sf::Time dt)
{
    world.update(dt);

    if (world.isGameOver())
    {
        stateStack->pushState(StateID::GameOver);
    }

    auto componentLabel = hpDisplay.getNthChild(0);
    auto* hpLabel = dynamic_cast<GUI::TextLabel*>(componentLabel.get());
    if (hpLabel)
        hpLabel->setText(std::to_string(world.getPlayerLife()));

    if (world.goNextLevel() && player.notMoving())
    {
        gen.generateMap();
        auto stream = gen.getMapAsStream();
        auto pos = gen.getEntrance();
        player.setPosition(pos);
        map.loadMap(stream);
        world.setNextLevel(false);
    }

    return false;
}

void Game::draw()
{
    context.texture->draw(world);

    if (!world.isGameOver())
    {
        context.texture->draw(hpDisplay);
    }
}