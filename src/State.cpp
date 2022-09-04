#include "State.h"

#include "StateStack.h"

State::State(StateStack& stateStack, Context context)
{
    this->context = context;
    this->stateStack = &stateStack;
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