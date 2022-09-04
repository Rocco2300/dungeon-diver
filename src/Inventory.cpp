#include "Inventory.h"

#include "Player.h"
#include "Button.h"
#include "StateStack.h"

Inventory::Inventory(StateStack& stateStack, Context context)
    : State(stateStack, context), selectedItem(0)
{
    auto& containerBG = gui.getBackgoundRef();
    gui.setSize({40, 50});
    gui.setArrowSelector(true);
    gui.setPosition({2.f, 14.f});

    containerBG.setFillColor(sf::Color::Black);
    containerBG.setOutlineThickness(1);
    containerBG.setOutlineColor(sf::Color::White);
    containerBG.setSize(gui.getSize());

    this->items = &context.world->getPlayerRef().getItemsRef();

    for (size_t i = 0; i < items->size(); i++)
    {
        auto button = std::make_shared<GUI::Button<std::function<void()>>>();
        button->setCallback([this, i] ()
        {
            items->at(i)->use();
        });
        button->setPosition({4.f, i * 10.f});
        button->setSize({36, 8});
        button->setText((items->at(i)) ? items->at(i)->getName() : "...");

        gui.pack(button);
    }
}

bool Inventory::handleEvent(const sf::Event &event)
{
    gui.handleEvent(event);

    switch (event.key.code)
    {
        case sf::Keyboard::Escape:
            stateStack->popState();
            break;
        default:
            break;
    }

    return false;
}

bool Inventory::update(sf::Time dt)
{
    gui.update(dt);

    return true;
}

void Inventory::draw()
{
    context.texture->draw(gui);
}