#include "Inventory.h"

#include "Button.h"
#include "Player.h"
#include "StateStack.h"

Inventory::Inventory(StateStack& stateStack, Context context)
    : State(stateStack, context)
{
    gui.setSize({40, 50});
    gui.setArrowSelector(true);
    gui.setPosition({2.f, 14.f});
    gui.setTransition(true);

    gui.setSize(gui.getSize());
    gui.setOutlineThickness(1);
    gui.setOutlineColor(sf::Color::White);
    gui.setBackgroundColor(sf::Color::Black);

    this->items = &context.world->getPlayerRef().getItemsRef();

    for (size_t i = 0; i < items->size(); i++)
    {
        auto button = std::make_shared<GUI::Button<std::function<void()>>>();
        button->setCallback(
                [this, i]()
                {
                    items->use(i);
                    updateButtonLabels();
                });
        button->setPosition({4.f, i * 10.f});
        button->setSize({36, 8});
        button->setText((items->at(i)) ? items->at(i)->getName() : "...");

        gui.pack(button);
    }
}

bool Inventory::handleEvent(const sf::Event& event)
{
    gui.handleEvent(event);

    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Tab:
            stateStack->popState();
            //            gui.transition(Transition::Close);
            break;
        default:
            break;
        }
    }

    return false;
}

bool Inventory::update(sf::Time dt)
{
    //    if (gui.isDoneScaling() && gui.getBackgoundRef().getSize().y == 0.f)
    //        stateStack->popState();

    gui.update(dt);

    return true;
}

void Inventory::draw() { context.texture->draw(gui); }

void Inventory::updateButtonLabels()
{
    for (size_t i = 0; i < items->size(); i++)
    {
        using ButtonType = GUI::Button<std::function<void()>>;
        auto button      = dynamic_cast<ButtonType*>(gui.getNthChild(i).get());

        auto buttonText = items->at(i) ? items->at(i)->getName() : "...";

        button->setText(buttonText);
    }
}