#include "GameState.h"



GameState::GameState(StateStack & stack) {
	
	stateStack = &stack;
	stateID = States::GAME;
}

void GameState::draw(){

}

bool GameState::handleEvent(const sf::Event& event) {

	if (event.key.code == sf::Keyboard::Up) {
		// do shit
	}
	if (event.key.code == sf::Keyboard::Down) {
		// do other shit
	}
	return true;
}


bool GameState::update(sf::Time dt) {
	return true;
}