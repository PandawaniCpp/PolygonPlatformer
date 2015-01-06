
#include "Credits.h"


Credits::Credits(StateStack & stack, Game * game)
	: State(stack, game), textVisible(true), textEffectTime(sf::Time::Zero) {

	y = x = 0;
	stateID = States::CREDITS;
	font.loadFromFile("./textures/coolFont.ttf");
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);
	gamePtr->gameWindow.setView(gamePtr->view);

	texture.loadFromFile("./textures/title4.jpg");
	background.setTexture(texture);
	background.setPosition(0.f, 0.f);

	for (int i = 0; i < 5; i++){
		text[i].setStyle(sf::Text::Bold);
		text[i].setColor(sf::Color::Red);
		text[i].setFont(font);
		text[i].setCharacterSize(65);
	}
	
	text[0].setString("Tomasz Kogowski");
	text[1].setString("Marcin Jarzebski");
	text[2].setString("Jakub Kierejsza");
	text[3].setString("Jakub Nietubski");
	text[4].setString("Pod nadzorem\n Pawla \"Pandy\" Kaczynskiego");

}

void Credits::draw(sf::RenderTarget& target) {
	gamePtr->gameWindow.draw(background);
	for (int i = 0; i < 5; ++i)
		gamePtr->gameWindow.draw(text[i]);
}

bool Credits::update(sf::Time dt) {
	
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	
	x=x+1;
	y=y+1;
	unsigned center = gamePtr->view.getCenter().y + gamePtr->graphics.getWindowHeight() / 6;

	background.setScale((float)gamePtr->graphics.getWindowWidth() / texture.getSize().x,
		(float)gamePtr->graphics.getWindowHeight() / texture.getSize().y);
	
	for (int i = 5; i > 0; --i){
		text[i].setOrigin(text[i].getLocalBounds().width / 2, text[i].getLocalBounds().height / 2);
		
	}
	if (y<500)
	text[0].setPosition(1400 - x, 800 - y);
	if (x<500)
	text[1].setPosition(-100 + x, -100 + y);
	if (y<500)
	text[2].setPosition(1500 -x, y);
	if (x<500)
	text[3].setPosition( 300, y);
	if (x<450)
	text[4].setPosition(x ,600- y);

	if (x > 1000)
	{
		requestStateClear();
		requestStackPush(States::TITLE);
	}

	return true;
}

bool Credits::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
		requestStateClear();
		requestStackPush(States::TITLE);
	}

	return true;
}
