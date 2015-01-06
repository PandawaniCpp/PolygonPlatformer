
#include "PauseState.h"


PauseState::PauseState(StateStack & stack, Game * game)
	: State(stack, game) {
	stateID = States::PAUSE;
	klawisz = 3;
	font.loadFromFile("./textures/coolFont.ttf");
	for (int i = 0; i < 4; i++){
		text[i].setStyle(sf::Text::Bold);
		text[i].setColor(sf::Color::Red);
		text[i].setFont(font);
	}
	
	text[0].setString("Leave Game");
	text[1].setString("Menu");
	text[2].setString("Options");
	text[3].setString("Back to Game");
	
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(10000, 10000));

}

void PauseState::draw(sf::RenderTarget& target) {

	gamePtr->gameWindow.draw(backgroundShape);
	for (int i = 0; i < 4; ++i)
		gamePtr->gameWindow.draw(text[i]);
	
}

bool PauseState::update(sf::Time dt) {

	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());

	unsigned center = gamePtr->view.getCenter().y + gamePtr->graphics.getWindowHeight() / 4;
	for (int i = 3; i >= 0; --i){
		text[i].setCharacterSize(45);
		text[i].setColor(sf::Color::White);

		text[i].setOrigin(text[i].getLocalBounds().width / 2, text[i].getLocalBounds().height / 2);

		text[i].setPosition(gamePtr->view.getCenter().x, center - 50 * i);

	}
	text[klawisz].setColor(sf::Color::Red);
	return true;
}

bool PauseState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
		if (klawisz == 3)   //back to game
		{
			requestStackPop();
		}
		else if (klawisz == 2)
			requestStackPush(States::OPTIONS);
		else if (klawisz == 1)
		{
			//requestStateClear();
			requestStackPop();
			requestStackPop();
			requestStackPush(States::MENU);
		}
		else if (klawisz == 0){ 
			//leave the game
			exit(1);
			requestStateClear();
			gamePtr->gameWindow.close();
		}
	}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
			--klawisz;
			if (klawisz < 0)
				klawisz = 3;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
			++klawisz;
			if (klawisz > 3)
				klawisz = 0;
		}
		return true;
	}
