
#include "PauseState.h"


PauseState::PauseState(StateStack & stack, Game * game)
	: State(stack, game) {
	stateID = States::PAUSE;
}

void PauseState::draw(sf::RenderTarget& target) {

	backgroundMenu.load(Textures::PAUSE, "./textures/Pause.png");
	SceneNode::Ptr tmp(new SceneNode);
	root.attachChild(tmp);
	tmp->setTexture(backgroundMenu.get(Textures::PAUSE));
	//tmp->setPosition((float)gamePtr->gameWindow.getSize().x/2, (float)gamePtr->gameWindow.getSize().y/2);
	//tmp->setOrigin((float)gamePtr->gameWindow.getSize().x / 2, (float)gamePtr->gameWindow.getSize().y / 2);
	//tmp->setPosition(stateStack->zmiennaX, stateStack->zmiennaY);
	tmp->setPosition(gamePtr->gameWindow.getView().getCenter().x /2, gamePtr->gameWindow.getView().getCenter().y/2 );
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
