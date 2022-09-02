#include "Item.h"

Item::Item(ItemType type, std::string name, Player& player)
{
    this->player = &player;

    this->type = type;
    this->name = name;
}

void Item::use()
{
    switch(type)
    {
    case ItemType::Heal:
    case ItemType::Damage:
    default:
        break;
    }
}