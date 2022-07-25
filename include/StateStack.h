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

    sf::RenderTexture* texture;
    std::vector<State::Ptr> stack;
    std::vector<PendingChange> pendingChanges;
    std::map<StateID, std::function<State::Ptr()>> factories;

public:
    StateStack() = default;
    StateStack(sf::RenderTexture& texture);
    ~StateStack() = default;

    template <typename T>
    void registerState(StateID stateID)
    {
        factories[stateID] = [this] ()
        {
            return State::Ptr(new T(*this, *texture));
        };
    }

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
