
#include "PauseState.h"


PauseState::PauseState(StateStack & stack, Game * game)
	: State(stack, game) {
	stateID = States::PAUSE;
	font.loadFromFile("./textures/coolFont.ttf");
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);
	text.setFont(font);
	text.setString("Press ENTER to continue\n\n    Press ESCAPE to exit\n\n\  Press R to restart game");
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(10000, 10000));

}

void PauseState::draw(sf::RenderTarget& target) {

	gamePtr->gameWindow.draw(backgroundShape);
	gamePtr->gameWindow.draw(text);
	
}

bool PauseState::update(sf::Time dt) {
	
	text.setCharacterSize(45);

	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());

	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

	text.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);
	
	return true;
}

bool PauseState::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R){
		requestStateClear();
		stateStack->pushState(States::GAME);
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		requestStateClear();			
		gamePtr->gameWindow.close();		
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
		requestStackPop();
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A){
		gamePtr->graphics.setWindowHeight(400);
	}
	return true;
}
