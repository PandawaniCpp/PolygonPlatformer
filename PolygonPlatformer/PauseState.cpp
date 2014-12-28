
#include "PauseState.h"


PauseState::PauseState(StateStack & stack, Game * game)
	: State(stack, game) {
	stateID = States::PAUSE;
	fontek.loadFromFile("./textures/czcionka.ttf");
}

void PauseState::draw(sf::RenderTarget& target) {

	
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Green);
	text.setCharacterSize(25);
	text.setFont(fontek);
	text.setString("Press ENTER to continue\n\nPress ESCAPE to exit(1)\n\n\And for God sake DO NOT PRESS SPACEBAR");
	text.setPosition((gamePtr->gameWindow.getView().getSize().x / 2)-200, (gamePtr->gameWindow.getView().getSize().y / 2)-30);
	
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
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A){
	
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {

		//requestStackPop();
		//requestStackPop();
		exit(1);
		//requestStateClear();			//not working
		//gamePtr->gameWindow.close();	vector error
		//requestStackPush(States::MENU);
	}
	
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
		requestStackPop();
	}
	
	return true;
}
