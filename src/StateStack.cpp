#include "StateStack.h"

#include <cassert>

StateStack::StateStack(Context& context)
{
    this->context = &context;
}

template <typename T>
void StateStack::registerState(StateID stateID)
{
    factories[stateID] = [this] ()
    {
        return State::Ptr(new T(*this, context));
    }
}

State::Ptr StateStack::createState(StateID stateID)
{
    auto found = factories.find(stateID)
    assert(found != factories.end());

    return found->second;
}