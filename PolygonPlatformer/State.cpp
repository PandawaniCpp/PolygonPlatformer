#include "State.h"
#include "StateStack.h"


State::State() {
}

State::~State() {
}

States::ID State::getStateID() {
	return stateID;
}


void State::requestStackPush(States::ID stateID) {
	stateStack->pushState(stateID);
}

void State::requestStackPop() {
	stateStack->popState();
}

void State::requestStateClear() {
	stateStack->clearStates();
}
