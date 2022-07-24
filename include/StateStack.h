#pragma once

#include <functional>

#include "State.h"
#include "StateIdentifiers.h"

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
        PendingChange(Action action, StateID stateID = StateID::None) 
            : action{action}, stateID{stateID} {}

        Action action;
        StateID stateID;
    };

    std::vector<State::Ptr> stack;
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

    bool isEmpty() const;

private:
    State::Ptr createState(StateID stateID);
    void applyPendingChanges(); 
};
