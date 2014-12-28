
#include "TitleState.h"


TitleState::TitleState(StateStack & stack, Game * game)
	: State(stack, game) {

	backgroundMenu.load(Textures::TITLE, "./textures/Title.png");
	SceneNode::Ptr tmp(new SceneNode);
	root.attachChild(tmp);
	tmp->setTexture(backgroundMenu.get(Textures::TITLE));
	stateID = States::TITLE;
}

void TitleState::draw(sf::RenderTarget& target) {
	
	root.draw(target);

}

bool TitleState::update(sf::Time dt) {
	return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
	
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(States::MENU);
	}
	return true;
}
