
#include "MenuState.h"


MenuState::MenuState(StateStack & stack) {
	stateStack = &stack;
	stateID = States::MENU;
}

void MenuState::draw() {

	ptrWindow->draw(background);
	ptrWindow->draw(text);
}

bool MenuState::update(sf::Time dt) {
	return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
	
	if (event.type == sf::Event::KeyPressed) {
	requestStackPop();        
	requestStackPush(States::GAME); 
	}
	return true;
}
