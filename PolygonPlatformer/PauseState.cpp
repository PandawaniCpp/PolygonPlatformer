
#include "PauseState.h"


PauseState::PauseState(StateStack & stack) {

	//backgroundMenu.load(Textures::PAUSE, "./textures/Pause.png");
	///SceneNode::Ptr tmp(new SceneNode);
	//root.attachChild(tmp);
	//tmp->setTexture(backgroundMenu.get(Textures::PAUSE));
	stateStack = &stack;
	stateID = States::TITLE;
}

void PauseState::draw(sf::RenderTarget& target) {

	root.draw(target);

}

bool PauseState::update(sf::Time dt) {
	return true;
}

bool PauseState::handleEvent(const sf::Event& event) {
	//if (event.key.code == sf::Keyboard::A)  dziala
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {

		exit(1);
	}
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();

	}
	
	return true;
}
