#include "State.h"

#include "StateStack.h"

State::State(StateStack& stateStack, Context& context)
{
    this->stateStack = &stateStack;
    this->context = &context;
}

void State::requestStackPush(StateID stateID)
{
    stateStack->pushState(stateID);
}

void State::requestStackClear()
{
    stateStack->clearStates();
}

void State::requestStackPop()
{
    stateStack->popState();
}