#include "ItemFactory.h"

#include "CSV.h"
#include "Player.h"

ItemFactory::ItemFactory(Player &player)
    : player{&player}
{

}

Item* ItemFactory::getItem()
{
    CSV<Label> csv;
    csv.load(std::string(PROJ_PATH) + "/csv/Items.csv");

    return new Item(
        stringToItemType(csv(0, Label::Type)),
        csv(0, Label::Name),
        atoi(csv(0, Label::Value).c_str()),
        *player
    );
}

void ItemFactory::givePlayerItem()
{
    auto item = getItem();
    player->giveItem(item);
}

void ItemFactory::setPlayer(Player &player)
{
    this->player = &player;
}

ItemType ItemFactory::stringToItemType(std::string type)
{
    if (type == "heal")
        return ItemType::Heal;
    else
        return ItemType::Damage;
}
