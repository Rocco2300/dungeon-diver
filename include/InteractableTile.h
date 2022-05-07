#pragma once

class InteractableTile
{
protected:
    bool interactable = true;
public:
    InteractableTile();
    virtual ~InteractableTile() { }

    virtual void onInteract() = 0;
};

