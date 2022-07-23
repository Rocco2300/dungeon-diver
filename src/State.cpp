#include "State.h"

State::State(StateStack& stateStack, Context& context)
{
    this->stateStack = &stateStack;
    this->context = &context;
}

