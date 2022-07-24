#include "StateStack.h"

#include <cassert>

StateStack::StateStack(Context& context)
{
    this->context = &context;
}

void StateStack::draw()
{
    for (auto it = stack.begin(); it != stack.end(); it++)
    {
        (*it)->draw();
    }
}

void StateStack::update(sf::Time dt)
{
    for (auto it = stack.rbegin(); it != stack.rend(); it++)
    {
        if (!(*it)->update(dt))
            break;
    }

    applyPendingChanges();
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto it = stack.rbegin(); it != stack.rend(); it++)
    {
        if (!(*it)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}   

void StateStack::pushState(StateID stateID)
{
    pendingChanges.push_back({Action::Push, stateID});
}

void StateStack::clearStates()
{
    pendingChanges.push_back({Action::Clear});
}

void StateStack::popState()
{
    pendingChanges.push_back({Action::Clear});
}

bool StateStack::isEmpty() const 
{
    return stack.empty();
}

State::Ptr StateStack::createState(StateID stateID)
{
    auto found = factories.find(stateID);
    assert(found != factories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for (auto& change : pendingChanges)
    {
        switch (change.action)
        {
        case Action::Push:
            stack.push_back(std::move(createState(change.stateID)));
            break;
        case Action::Pop:
            stack.pop_back();
            break;
        case Action::Clear:
            stack.clear();
            break;
        default:
            break;
        }
    }

    pendingChanges.clear();
}
