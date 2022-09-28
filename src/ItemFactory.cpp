#include "ItemFactory.h"

#include "CSV.h"
#include "Player.h"

#include <chrono>
#include <random>

ItemFactory::ItemFactory(Player& player)
    : player{&player}
{}

Item* ItemFactory::getItem()
{
    using u32 = unsigned int;
    using u64 = unsigned long long;

    CSV<Label> csv;
    csv.load(std::string(PROJ_PATH) + "/csv/Items.csv");

    static u64 timeSeed = std::chrono::high_resolution_clock::now()
                                  .time_since_epoch()
                                  .count();
    static std::seed_seq ss{u32(timeSeed & 0xffffffff), u32(timeSeed >> 32)};

    static std::mt19937                       rng(ss);
    static std::uniform_int_distribution<u32> unif(0, 2);

    auto index = unif(rng);

    auto name     = csv(index, Label::Name);
    auto value    = atoi(csv(index, Label::Value).c_str());
    auto itemType = stringToItemType(csv(index, Label::Type));
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
    if (type == "heal")
        return ItemType::Heal;
    else if (type == "mov")
        return ItemType::Mov;
    else if (type == "dmg")
        return ItemType::Damage;
    else if (type == "warp")
        return ItemType::Warp;

    return ItemType::None;
}
