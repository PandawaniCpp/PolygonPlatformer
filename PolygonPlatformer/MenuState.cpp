
#include "MenuState.h"


MenuState::MenuState(StateStack & stack) {
	
	backgroundMenu.load(Textures::MENU, "./textures/Menu.png");
	SceneNode::Ptr tmp(new SceneNode);
	root.attachChild(tmp);
	tmp->setTexture(backgroundMenu.get(Textures::MENU));
	stateStack = &stack;
	stateID = States::MENU;
}

void MenuState::draw (sf::RenderTarget& target) {

	root.draw(target);
	
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
