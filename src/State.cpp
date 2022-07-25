#include "State.h"

#include "StateStack.h"

State::State(StateStack& stateStack, sf::RenderTexture& texture)
{
    this->stateStack = &stateStack;
    this->texture = &texture;
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