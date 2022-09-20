#include "ItemFactory.h"

#include "CSV.h"
#include "Player.h"

ItemFactory::ItemFactory(Player& player)
    : player{&player}
{}

Item* ItemFactory::getItem()
{
    CSV<Label> csv;
    csv.load(std::string(PROJ_PATH) + "/csv/Items.csv");

    auto name     = csv(1, Label::Name);
    auto value    = atoi(csv(1, Label::Value).c_str());
    auto itemType = stringToItemType(csv(1, Label::Type));
    return new Item(itemType, name, value, *player);
}

void ItemFactory::givePlayerItem()
{
    auto item = getItem();
    player->giveItem(item);
}

void ItemFactory::setPlayer(Player& player) { this->player = &player; }

ItemType ItemFactory::stringToItemType(std::string type)
{
    if (type == "heal") return ItemType::Heal;
    else
        return ItemType::Damage;
}
