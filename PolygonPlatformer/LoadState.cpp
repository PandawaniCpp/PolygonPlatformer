
#include "LoadState.h"


LoadState::LoadState(StateStack & stack, Game * game)
	: State(stack, game) {
	
	stateID = States::LOAD;
	
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);
	gamePtr->gameWindow.setView(gamePtr->view);

	texture.loadFromFile("./textures/title4.jpg");
	background.setTexture(texture);
	background.setPosition(0.f, 0.f);

	font.loadFromFile("./textures/coolFont.ttf");
	text.setCharacterSize(gamePtr->graphics.getWindowHeight() / 3);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::Red);

		text.setFont(font);
	
	text.setString("LOADING");
	
	backgroundShapeHelp.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShapeHelp.setSize(sf::Vector2f(10000, 10000));

}

void LoadState::draw(sf::RenderTarget& target) {

		gamePtr->gameWindow.draw(background);
			gamePtr->gameWindow.draw(text);
			requestStackPop();
			requestStackPush(States::GAME);
		
}

bool LoadState::update(sf::Time dt) {

	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	background.setScale((float)gamePtr->graphics.getWindowWidth() / texture.getSize().x,
		(float)gamePtr->graphics.getWindowHeight() / texture.getSize().y);
	unsigned center = gamePtr->view.getCenter().y + gamePtr->graphics.getWindowHeight() / 6;
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);

	
	return true;

}

bool LoadState::handleEvent(const sf::Event& event) {

	return true;
}

//text.setPosition(gamePtr->view.getCenter().x - gamePtr->graphics.getWindowWidth()/100, gamePtr->view.getCenter().y - gamePtr->graphics.getWindowHeight()/7);
//text.setPosition((gamePtr->gameWindow.getView().getSize().x / 2) - 170,  (gamePtr->gameWindow.getView().getSize().y / 2) - 130);
//text.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);
//text.setPosition(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);