#include "Item.h"

#include "Player.h"

Item::Item(ItemType type, std::string name, int value, Player& player)
{
    this->player = &player;

    this->type  = type;
    this->name  = name;
    this->value = value;
}

void Item::use()
{
    switch (type)
    {
    case ItemType::Heal:
        player->setHP(player->getHp() + value);
        break;
    case ItemType::Damage:
        break;
    case ItemType::Mov:
        player->setHook(value);
        break;
    case ItemType::Warp:
        player->setTurns(value);
        break;
    default:
        break;
    }
}

std::string Item::getName() { return name; }