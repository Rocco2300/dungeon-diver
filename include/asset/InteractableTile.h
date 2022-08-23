#pragma once

#include "Tile.h"

class InteractableTile : public Tile
{
protected:
    bool interactable = true;
public:
    InteractableTile() = default;
    virtual ~InteractableTile() = default;

    virtual void onInteract() = 0;
};

class ChestTile : public InteractableTile
{
private:
    
public:
    ChestTile() = default;

    void onInteract();
};

class DoorTile : public InteractableTile
{
private:
    
public:
    DoorTile() = default;

    void onInteract();
};

class PotTile : public InteractableTile
{
private:
    
public:
    PotTile() = default;

    void onInteract();
};

class ExitStairsTile : public InteractableTile
{
private:
    
public:
    ExitStairsTile() = default;

    void onInteract();
};