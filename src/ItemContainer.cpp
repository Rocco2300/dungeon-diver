#include "ItemContainer.h"

#include <cassert>

void ItemContainer::use(int index)
{
    if (items[index])
    {
        items.at(index)->use();
        items.at(index).reset();
    }
}

size_t ItemContainer::size()
{
    return items.size();
}

Item::Ptr& ItemContainer::at(int index)
{
    assert(index >= 0 && index < 5);

    return items[index];
}

const Item::Ptr& ItemContainer::at(int index) const
{
    assert(index >= 0 && index < 5);

    return items[index];
}

Item::Ptr& ItemContainer::operator[](int index)
{
    assert(index >= 0 && index < 5);

    return items[index];
}

const Item::Ptr& ItemContainer::operator[](int index) const
{
    assert(index >= 0 && index < 5);

    return items[index];
}

ItemContainer::iterator ItemContainer::begin()
{
    return items.begin();
}

ItemContainer::iterator ItemContainer::end()
{
    return items.end();
}