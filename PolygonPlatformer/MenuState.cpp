
#include "MenuState.h"


MenuState::MenuState(StateStack & stack) {
	//backgroundMenu.load(, "./textures/Menu.png");
	stateStack = &stack;
	stateID = States::MENU;
}

void MenuState::draw() {

	//ptrWindow->draw(backgroundMenu);
	
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
