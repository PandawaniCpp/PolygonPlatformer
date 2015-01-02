
#include "PauseState.h"


PauseState::PauseState(StateStack & stack, Game * game)
	: State(stack, game) {
	stateID = States::PAUSE;
	font.loadFromFile("./textures/coolFont.ttf");
}

void PauseState::draw(sf::RenderTarget& target) {

	
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);
	text.setCharacterSize(45);
	text.setFont(font);
	text.setString("Press ENTER to continue\n\n    Press ESCAPE to exit\n\n\  Press R to restart game");
	text.setPosition((gamePtr->gameWindow.getView().getSize().x / 2) - 170, (gamePtr->gameWindow.getView().getSize().y / 2) - 130);
	
	sf::RenderWindow& window = gamePtr->gameWindow;    
	window.setView(window.getDefaultView());
	sf::RectangleShape backgroundShape;    
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));    
	backgroundShape.setSize(sf::Vector2f(window.getSize()));
	window.draw(backgroundShape);
	window.draw(text);
	

}

bool PauseState::update(sf::Time dt) {
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
	
	return true;
}
