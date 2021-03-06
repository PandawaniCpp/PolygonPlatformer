﻿#include "StateStack.h"


StateStack::~StateStack() {

}

StateStack::StateStack(Game * game)
	: stateStack(), pendingList(), game(game), factories() {
}

void StateStack::update(sf::Time dt) {
	if (!stateStack.empty())
		stateStack.back()->update(dt);

	applyPendingChanges();

}
States::ID StateStack::getCurrentStateID() {	
	if (stateStack.empty())
		return States::NONE;
	else		
		return stateStack.back()->getStateID();

	}

void StateStack::draw (sf::RenderTarget& target) {
	
	for (State::Ptr & state : stateStack)  
		state->draw(target);
}


State::Ptr StateStack::createState(States::ID stateID) {
	auto found = factories.find(stateID);
	assert(found != factories.end());

	return found->second();
}
// Czemu to odpala gdy wszystkie są true?
void StateStack::handleEvent(const sf::Event& event) {
	for (auto itr = stateStack.rbegin(); itr != stateStack.rend(); ++itr)   
	{ 
		if (!(*itr)->handleEvent(event))           
		return; 
	}
	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID) {
	pendingList.push_back(PendingChange(PUSH, stateID));
}

void StateStack::popState() {
	pendingList.push_back(PendingChange(POP));
}

void StateStack::clearStates() {
	pendingList.push_back(PendingChange(CLEAR));
}

bool StateStack::isEmpty() const {
	return stateStack.empty();
}


void StateStack::applyPendingChanges() {
	for(PendingChange & change: pendingList) {
		switch (change.action) {
		case PUSH:
			stateStack.push_back(createState(change.stateID));
			break;

		case POP:
			stateStack.pop_back();
			break;

		case CLEAR:
			for (State::Ptr & state : stateStack)
				stateStack.clear();
			break;
		}
	}

	pendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action), stateID(stateID) {
}
