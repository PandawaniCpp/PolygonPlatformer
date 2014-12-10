#include "StateStack.h"


StateStack::~StateStack() {

}

StateStack::StateStack()
	: stateStack(), pendingList(), factories() {
}

void StateStack::update(sf::Time dt) {
	// Update only the top state. WHY?
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

void StateStack::draw() {
	// Draw all active states from bottom to top, WHY not the top only
	for (State::Ptr & state : stateStack)  // FOREACH
		state->draw();
}


State::Ptr StateStack::createState(States::ID stateID) {
	auto found = factories.find(stateID);
	assert(found != factories.end());

	return found->second();
}
// Czemu to odpala gdy wszystkie są true?
// Jak to zrobić? Panda używa klasy Command 
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

//Zapytać Pandy co robią OnActive i OnDestroy
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
