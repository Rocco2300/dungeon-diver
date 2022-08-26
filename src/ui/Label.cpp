#include "Label.h"

namespace GUI
{

void TextLabel::setAllignment(Allign allignment)
{
    this->allignment = allignment;
    applyAllignment();
}

void TextLabel::setText(std::string str)
{
    text.setString(str);
    applyAllignment();
}

void TextLabel::applyAllignment()
{
    int tx, ty;
    switch (allignment)
    {
    case Allign::Left:
        tx = 0;
        ty = (size.y - text.getSize().y) / 2;
        text.setPosition(sf::Vector2f(tx, ty));
        break;
    case Allign::Center:
        tx = (size.x - text.getSize().x) / 2;
        ty = (size.y - text.getSize().y) / 2;
        text.setPosition(sf::Vector2f(tx, ty));
        break;
    case Allign::Right:
        tx = (size.x - text.getSize().x);
        ty = (size.y - text.getSize().y) / 2;
        text.setPosition(sf::Vector2f(tx, ty));
        break;
    };
}

bool TextLabel::isSelectable() const
{
    return false;
}

void TextLabel::handleEvent(const sf::Event& event)
{

}

void TextLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform transform;
    transform.translate(pos);
    states.transform *= transform;

    target.draw(text, states);
}

void SpriteLabel::setAllignment(Allign allignment)
{
    this->allignment = allignment;
    applyAllignment();
}

void SpriteLabel::setSprite(std::string str)
{
    sprite.setTexture(AssetManager::getTexture(str));
    applyAllignment();
}

void SpriteLabel::setSpriteRect(sf::IntRect rect)
{
    sprite.setTextureRect(rect);
    applyAllignment();
}

void SpriteLabel::applyAllignment()
{
    int tx, ty;
    int sprWidth = sprite.getLocalBounds().width;
    int sprHeight = sprite.getLocalBounds().height;

    switch (allignment)
    {
    case Allign::Left:
        tx = 1;
        ty = (size.y - sprHeight) / 2;
        sprite.setPosition(sf::Vector2f(tx, ty));
        break;
    case Allign::Center:
        tx = (size.x - sprWidth) / 2;
        ty = (size.y - sprHeight) / 2;
        sprite.setPosition(sf::Vector2f(tx, ty)); 
        break;
    case Allign::Right:
        tx = (size.x - sprWidth) - 1;
        ty = (size.y - sprHeight) / 2;
        sprite.setPosition(sf::Vector2f(tx, ty));
        break;
    };
}

bool SpriteLabel::isSelectable() const
{
    return false;
}

void SpriteLabel::handleEvent(const sf::Event& event)
{

}

void SpriteLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform transform;
    transform.translate(pos);
    states.transform *= transform;

    target.draw(sprite, states);
}

};