
#include "TitleState.h"


TitleState::TitleState(StateStack & stack, Game * game)
	: State(stack, game) {

	stateID = States::TITLE;
	text.setStyle(sf::Text::Italic);
	text.setColor(sf::Color::White);
	text.setFont(font);
	text.setString("Title");
	font.loadFromFile("./textures/coolFont.ttf");
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(10000, 10000));

}

void TitleState::draw(sf::RenderTarget& target) {
	

	gamePtr->gameWindow.draw(backgroundShape);
	gamePtr->gameWindow.draw(text);

}

bool TitleState::update(sf::Time dt) {
	
	text.setCharacterSize(gamePtr->graphics.getWindowHeight() / 4);

	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);

	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);
	return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
	

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A){
		gamePtr->graphics.setWindowHeight(630);
		gamePtr->graphics.setWindowWidth(1120);
		gamePtr->view.setSize(1120, 630);
		gamePtr->gameWindow.setSize(sf::Vector2u(1120, 630));
		
		requestStackPop();
		requestStackPush(States::TITLE);
	}

	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
		requestStackPop();
		requestStackPush(States::MENU);
	}
	return true;
}

//text.setPosition(gamePtr->graphics.getWindowWidth()/2, gamePtr->graphics.getWindowHeight()/2);