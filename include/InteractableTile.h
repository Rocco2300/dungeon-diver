#pragma once

class InteractableTile
{
public:
    InteractableTile();
    virtual ~InteractableTile() { }

    virtual void onInteract() = 0;
};

