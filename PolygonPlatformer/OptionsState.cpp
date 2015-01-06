
#include "OptionsState.h"


OptionsState::OptionsState(StateStack & stack, Game * game)
	: State(stack, game) {
	
	risk = 0;
	isCute = false;
	stateID = States::TITLE;
	klawisz = 3;
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);
	gamePtr->gameWindow.setView(gamePtr->view);


	texture.loadFromFile("./textures/title4.jpg");
	cute.loadFromFile("./textures/cute2.jpg");
	background.setTexture(texture);
	background.setPosition(0.f, 0.f);

	font.loadFromFile("./textures/coolFont.ttf");
	for (int i = 0; i < 4; i++){
		text[i].setStyle(sf::Text::Bold);
		text[i].setColor(sf::Color::Red);
		text[i].setFont(font);
	}
	text[0].setString("Back");
	text[1].setString("Awesomeness level");
	text[2].setString("Useless option bar");
	text[3].setString("Cuteness overload");
}

void OptionsState::draw(sf::RenderTarget& target) {
	
	if (isCute)
	{
		gamePtr->gameWindow.draw(background);
	}
	else
	{
		gamePtr->gameWindow.draw(background);
		for (int i = 0; i < 4; ++i)
			gamePtr->gameWindow.draw(text[i]);
	}
}

bool OptionsState::update(sf::Time dt) {
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	if (isCute)
	{
		background.setTexture(cute);
		background.setScale((float)gamePtr->graphics.getWindowWidth() / cute.getSize().x,
			(float)gamePtr->graphics.getWindowHeight() / cute.getSize().y);
	}
	else {
		background.setTexture(texture);
		background.setScale((float)gamePtr->graphics.getWindowWidth() / texture.getSize().x,
			(float)gamePtr->graphics.getWindowHeight() / texture.getSize().y);
	}
	unsigned center = gamePtr->view.getCenter().y + gamePtr->graphics.getWindowHeight() / 6;
	
	text[1].setString("Awesomeness level "+std::to_string(stateStack->awesomeness));
	for (int i = 3; i >= 0; --i){
		text[i].setCharacterSize(65);
		text[i].setColor(sf::Color::White);


		text[i].setOrigin(text[i].getLocalBounds().width / 2, text[i].getLocalBounds().height / 2);

		text[i].setPosition(gamePtr->view.getCenter().x, center - 75 * i);

	}
	text[klawisz].setColor(sf::Color::Red);
	return true;
}

bool OptionsState::handleEvent(const sf::Event& event) {
	if (event.type==sf::Event::KeyPressed)
		if (isCute) isCute = false;
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
		
		if (klawisz == 0)
		{
			requestStackPop();
		}
		if (klawisz == 3)
		 {
			 isCute = true;
		 }
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
	{
		if (klawisz == 1)
			--stateStack->awesomeness;
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
	{
		if (klawisz == 1)
				++stateStack->awesomeness;
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
	/*
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A){
		gamePtr->graphics.setWindowHeight(600);
		gamePtr->graphics.setWindowWidth(800);

		gamePtr->gameWindow.setSize(sf::Vector2u(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight()));

		gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
		gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);

		text.setCharacterSize(gamePtr->graphics.getWindowHeight() / 4);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

		gamePtr->gameWindow.setView(gamePtr->view);
	}
	*/

}

