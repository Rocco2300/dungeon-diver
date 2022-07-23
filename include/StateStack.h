#pragma once

#include <functional>

#include "State.h"

enum class StateID
{
    Title,
    MainMenu,
    Game,
};

class StateStack
{
public:
    enum class Action
    {
        Push,
        Pop,
        Clear
    };
private:
    struct PendingChange
    {
        Action action;
        StateID stateID;
    };

    std::vector<State> stack;
    std::vector<PendingChange> pendingChanges;
    Context* context;
    std::map<StateID, std::function<State::Ptr()>> factories;

public:
    StateStack(Context& context);
    ~StateStack() = default;

    template <typename T>
    void registerState(StateID stateID);

    void draw();
    void update(sf::Time dt);
    void handleEvent(const sf::Event& event);

    void pushState(StateID stateID);
    void clearStates();
    void popState();

private:
    State::Ptr createState(StateID stateID);
    void applyPendingChanges(); 
};
