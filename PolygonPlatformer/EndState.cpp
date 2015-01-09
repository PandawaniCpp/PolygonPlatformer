
#include "EndState.h"


EndState::EndState(StateStack & stack, Game * game)
	: State(stack, game), textVisible(true), textEffectTime(sf::Time::Zero) {

	stateID = States::END;
	font.loadFromFile("./textures/coolFont.ttf");
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);
	gamePtr->gameWindow.setView(gamePtr->view);

	texture.loadFromFile("./textures/title4.jpg");
	background.setTexture(texture);
	background.setPosition(0.f, 0.f);

	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Blue);
	text.setFont(font);
}

void EndState::draw(sf::RenderTarget& target) {
	gamePtr->gameWindow.draw(background);
	if (textVisible)
		gamePtr->gameWindow.draw(text);

}

bool EndState::update(sf::Time dt) {

	unsigned center = gamePtr->view.getCenter().y + gamePtr->graphics.getWindowHeight() / 6;

	background.setScale((float)gamePtr->graphics.getWindowWidth() / texture.getSize().x,
		(float)gamePtr->graphics.getWindowHeight() / texture.getSize().y);
	text.setCharacterSize(gamePtr->graphics.getWindowHeight() / 4);

	text.setString(" Game Over\nBitch");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

	text.setPosition(gamePtr->view.getCenter().x + gamePtr->graphics.getWindowWidth() / 6, gamePtr->view.getCenter().y);

	textEffectTime += dt;

	if (textVisible) {
		if (textEffectTime >= sf::seconds(0.4f)) {
			textVisible = !textVisible;
			textEffectTime = sf::Time::Zero;
		}
	}
	else {
		if (textEffectTime >= sf::seconds(0.1f)) {
			textVisible = !textVisible;
			textEffectTime = sf::Time::Zero;
		}
	}

	return true;
}

bool EndState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
		requestStackPop();
		requestStackPop();
		requestStackPush(States::MENU);
	}
		
	return true;
}
