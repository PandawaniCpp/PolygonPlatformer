
#include "MenuState.h"


MenuState::MenuState(StateStack & stack, Game * game)
	: State(stack, game) {
	stateID = States::MENU;
	font.loadFromFile("./textures/coolFont.ttf");
	game->musicPlayer.play(Music::MENUTHEME);
}

void MenuState::draw (sf::RenderTarget& target) {

	text.setStyle(sf::Text::Italic);
	text.setColor(sf::Color::White);
	text.setCharacterSize(200);
	text.setFont(font);
	text.setString("Menu");
	text.setPosition((gamePtr->gameWindow.getView().getSize().x / 2) - 170, (gamePtr->gameWindow.getView().getSize().y / 2) - 130);

	sf::RenderWindow& window = gamePtr->gameWindow;
	window.setView(window.getDefaultView());
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));
	window.draw(backgroundShape);
	window.draw(text);
	
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
