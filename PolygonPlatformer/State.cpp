#include "State.h"
#include "StateStack.h"




State::State(StateStack & stack, Game * game)
	: stateStack(&stack), gamePtr(game) {
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

bool    State::handleEvent(const sf::Event& event){
	return true;
}
