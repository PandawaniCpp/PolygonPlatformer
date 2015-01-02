
#include "TitleState.h"


TitleState::TitleState(StateStack & stack, Game * game)
	: State(stack, game) {

	/*backgroundMenu.load(Textures::TITLE, "./textures/Title.png");
	SceneNode::Ptr tmp(new SceneNode);
	root.attachChild(tmp);
	tmp->setTexture(backgroundMenu.get(Textures::TITLE));*/
	stateID = States::TITLE;
	font.loadFromFile("./textures/coolFont.ttf");
}

void TitleState::draw(sf::RenderTarget& target) {
	
	text.setStyle(sf::Text::Italic);
	text.setColor(sf::Color::White);
	text.setCharacterSize(200);
	text.setFont(font);
	text.setString("Title");
	text.setPosition((gamePtr->gameWindow.getView().getSize().x / 2) - 170,  (gamePtr->gameWindow.getView().getSize().y / 2) - 130);

	sf::RenderWindow& window = gamePtr->gameWindow;
	window.setView(window.getDefaultView());
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));
	window.draw(backgroundShape);
	window.draw(text);

}

bool TitleState::update(sf::Time dt) {
	return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
	
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(States::MENU);
	}
	return true;
}
