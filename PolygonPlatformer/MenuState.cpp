
#include "MenuState.h"


MenuState::MenuState(StateStack & stack, Game * game)
	: State(stack, game) {
	game->musicPlayer.play(Music::MENUTHEME);
	stateID = States::MENU;
	font.loadFromFile("./textures/coolFont.ttf");
	text.setStyle(sf::Text::Italic);
	text.setColor(sf::Color::White);
	text.setFont(font);
	text.setString("Menu");
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(10000, 10000));
	
}

void MenuState::draw (sf::RenderTarget& target) {

	gamePtr->gameWindow.draw(backgroundShape);
	gamePtr->gameWindow.draw(text);
	
}

bool MenuState::update(sf::Time dt) {
	
	text.setCharacterSize(gamePtr->graphics.getWindowHeight() / 4);

	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);

	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);
	return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
	
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(States::GAME);
	}
	return true;
}

//text.setPosition(gamePtr->view.getCenter().x - gamePtr->graphics.getWindowWidth()/100, gamePtr->view.getCenter().y - gamePtr->graphics.getWindowHeight()/7);
//text.setPosition((gamePtr->gameWindow.getView().getSize().x / 2) - 170,  (gamePtr->gameWindow.getView().getSize().y / 2) - 130);
//text.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);
//text.setPosition(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);