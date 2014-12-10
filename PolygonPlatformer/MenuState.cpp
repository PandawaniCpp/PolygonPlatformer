
#include "MenuState.h"


MenuState::MenuState(StateStack & stack) {
	stateStack = &stack;
	stateID = States::MENU;
}

void MenuState::draw() {
//	game->gameWindow->draw(background);
	//game->gameWindow->draw(text);
}

bool MenuState::update(sf::Time dt) {
	return true;
}
/*
bool MenuState::handleEvent(const Command * command) {
	// "Press any key to continue"      
	if (command->commandType == Commands::PRESS_ANY_KEY) {
		requestStackPop();
		requestStackPush(States::LOAD);
	}

	return true;
}*/