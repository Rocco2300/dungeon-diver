#pragma once

#include "Item.h"

#include <array>
#include <memory>

class ItemContainer
{
public:
    using iterator = std::array<Item::Ptr, 5>::iterator;

private:
    std::array<Item::Ptr, 5> items;

public:
    ItemContainer()
        : items{}
    {}

    void use(int index);

    size_t size();

    Item::Ptr&       at(int index);
    const Item::Ptr& at(int index) const;

    Item::Ptr&       operator[](int index);
    const Item::Ptr& operator[](int index) const;

    iterator begin();
    iterator end();
};
