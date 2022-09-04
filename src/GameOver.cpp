#include "GameOver.h"

#include "Label.h"
#include "Constants.h"
#include "StateStack.h"

GameOver::GameOver(StateStack &stateStack, Context context)
    : State(stateStack, context)
{
    initUI();

    backgroundImage.create(
        WINDOW_SIZE,
        WINDOW_SIZE,
        sf::Color(0, 0, 0, 150)
    );

    if (!backgroundTexture.loadFromImage(backgroundImage))
        std::cerr << "Error loading background texture from image.\n";

    backgroudSprite.setTexture(backgroundTexture);
}

void GameOver::initUI()
{
    auto gameOverLabel = std::make_shared<GUI::TextLabel>();
    gameOverLabel->setSize({9 * 3, 5});
    gameOverLabel->setPosition({2, 2});
    gameOverLabel->setText("Game Over");

    int posX = WINDOW_SIZE / 2 - (9 * 3 + 8 + 4) / 2;
    int posY = WINDOW_SIZE / 2 - 9 / 2;

    auto a = std::make_shared<GUI::SpriteLabel>();

    container.setSize({9 * 3 + 8 + 4, 9});
    container.setPosition({static_cast<float>(posX), static_cast<float>(posY)});
    container.getBackgoundRef().setFillColor(sf::Color::Black);
    container.getBackgoundRef().setOutlineColor(sf::Color::White);
    container.getBackgoundRef().setOutlineThickness(1);
    container.getBackgoundRef().setSize({9 * 3 + 8 + 4, 9});

    container.pack(gameOverLabel);
}

bool GameOver::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
            stateStack->clearStates();
            stateStack->pushState(StateID::MainMenu);
        case sf::Keyboard::Enter:
            stateStack->clearStates();
            stateStack->pushState(StateID::Game);
        default:
            break;
        }
    }
    return true;
}

bool GameOver::update(sf::Time dt)
{
    return false;
}

void GameOver::draw()
{
    context.texture->draw(backgroudSprite);
    context.texture->draw(container);
}
