#pragma once

class InteractableTile
{
protected:
    bool interactable = true;
public:
    InteractableTile() = default;
    virtual ~InteractableTile() = default;

    virtual void onInteract() = 0;
};

