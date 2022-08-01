#include "Label.h"

namespace GUI
{

void Label::setAllignment(TextAllign allignment)
{
    this->allignment = allignment;
    applyAllignment();
}

void Label::setText(std::string str)
{
    text.setString(str);
    applyAllignment();
}

void Label::applyAllignment()
{
    int tx, ty;
    switch (allignment)
    {
    case TextAllign::Left:
        tx = 1;
        ty = (size.y - text.getSize().y) / 2;
        text.setPosition(sf::Vector2f(tx, ty));
        break;
    case TextAllign::Center:
        tx = (size.x - text.getSize().x) / 2;
        ty = (size.y - text.getSize().y) / 2;
        text.setPosition(sf::Vector2f(tx, ty));
        break;
    case TextAllign::Right:
        tx = (size.x - text.getSize().x) - 1;
        ty = (size.y - text.getSize().y) / 2;
        text.setPosition(sf::Vector2f(tx, ty));
        break;
    };
}

bool Label::isSelectable() const
{
    return false;
}

void Label::handleEvent(const sf::Event& event)
{

}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}

};