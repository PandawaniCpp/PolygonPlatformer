#include "GameState.h"



GameState::GameState(StateStack & stack):player(new Player),doSleep(true),gravity(0,-10.f),world(gravity) {
	
	stateStack = &stack;
	stateID = States::GAME;
    
   root.attachChild (player);
    textures.load (Textures::PLAYER, "./textures/player.png");
    player->setTexture (textures.get (Textures::PLAYER));
    player->setPosition (300.f, 300.f);

    world.SetAllowSleeping (doSleep);
}

void GameState::draw(sf::RenderTarget& target){
    root.draw (target);
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
    root.update (dt);
    return true;
}