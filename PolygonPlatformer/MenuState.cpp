
#include "MenuState.h"


MenuState::MenuState(StateStack & stack, Game * game)
	: State(stack, game) {
	game->musicPlayer.play(Music::MENUTHEME);
	stateID = States::MENU;
	klawisz = 2;
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);
	gamePtr->gameWindow.setView(gamePtr->view);


	texture.loadFromFile("./textures/title4.jpg");
	background.setTexture(texture);
	background.setPosition(0.f, 0.f);

	font.loadFromFile("./textures/coolFont.ttf");
	for (int i = 0; i < 3; i++){
		text[i].setStyle(sf::Text::Bold);
		text[i].setColor(sf::Color::Red);
		text[i].setFont(font);
	}
	text[0].setString("Leave");
	text[1].setString("Options");
	text[2].setString("Play");

	SceneNode::globalMoney = 0;
	SceneNode::currentWave = 1;
	SceneNode::fatOnMap = 0;
	SceneNode::fighterOnMap = 0;
	SceneNode::kamikazeOnMap = 0;
	SceneNode::swarmOnMap = 0;

}

void MenuState::draw(sf::RenderTarget& target) {

	gamePtr->gameWindow.draw(background);
	for (int i = 0; i < 3; ++i)
		gamePtr->gameWindow.draw(text[i]);

}

bool MenuState::update(sf::Time dt) {

	//text.setCharacterSize(gamePtr->graphics.getWindowHeight() / 4);
	//text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	//text.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);
	////gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	////gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);

	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	background.setScale((float)gamePtr->graphics.getWindowWidth() / texture.getSize().x,
		(float)gamePtr->graphics.getWindowHeight() / texture.getSize().y);
	unsigned center = gamePtr->view.getCenter().y + gamePtr->graphics.getWindowHeight() / 6;
	for (int i = 2; i >= 0; --i){
		text[i].setCharacterSize(65);
		text[i].setColor(sf::Color::White);

		text[i].setOrigin(text[i].getLocalBounds().width / 2, text[i].getLocalBounds().height / 2);

		text[i].setPosition(gamePtr->view.getCenter().x, center - 75 * i);

	}
	text[klawisz].setColor(sf::Color::Red);
	return true;

}

bool MenuState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
		if (klawisz == 2)
		{
			requestStackPop();
			requestStackPush(States::GAME);
		}
		else if (klawisz == 1)
		{
			requestStackPush(States::OPTIONS);
		}
		else if (klawisz == 0)
		{
			exit(1);
			requestStateClear();
			gamePtr->gameWindow.close();
		}
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
		--klawisz;
		if (klawisz < 0)
			klawisz = 2;
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
		++klawisz;
		if (klawisz > 2)
			klawisz = 0;
	}
	return true;
}

//text.setPosition(gamePtr->view.getCenter().x - gamePtr->graphics.getWindowWidth()/100, gamePtr->view.getCenter().y - gamePtr->graphics.getWindowHeight()/7);
//text.setPosition((gamePtr->gameWindow.getView().getSize().x / 2) - 170,  (gamePtr->gameWindow.getView().getSize().y / 2) - 130);
//text.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);
//text.setPosition(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);