
#include "MenuState.h"


MenuState::MenuState(StateStack & stack, Game * game)
	: State(stack, game) {
	game->musicPlayer.play(Music::MENUTHEME);
	stateID = States::MENU;
	klawisz = 3;
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	gamePtr->view.setCenter(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);
	gamePtr->gameWindow.setView(gamePtr->view);

	texture.loadFromFile("./textures/title4.jpg");
	background.setTexture(texture);
	background.setPosition(0.f, 0.f);

	font.loadFromFile("./textures/coolFont.ttf");
	for (int i = 0; i < 4; i++){
		text[i].setStyle(sf::Text::Bold);
		text[i].setColor(sf::Color::Red);

		text[i].setFont(font);
	}
	text[0].setString("Leave");
	text[1].setString("Options");
	text[2].setString("Instructions");
	text[3].setString("Play");
	

	SceneNode::globalMoney = 0;
	SceneNode::currentWave = 1;
	SceneNode::fatOnMap = 0;
	SceneNode::fighterOnMap = 0;
	SceneNode::kamikazeOnMap = 0;
	SceneNode::swarmOnMap = 0;

	helpPressed = false;
	help.setStyle(sf::Text::Italic);
	help.setFont(font);
	help.setColor(sf::Color::Yellow);
	help.setCharacterSize(150);
	help.setString(" To move left press A\n  To move right press D\n To jump press W\nTo shoot press K");
	backgroundShapeHelp.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShapeHelp.setSize(sf::Vector2f(10000, 10000));

}

void MenuState::draw(sf::RenderTarget& target) {

	if (!helpPressed){
		gamePtr->gameWindow.draw(background);
		for (int i = 0; i < 4; ++i)
			gamePtr->gameWindow.draw(text[i]);
	}
	else 
	{
		gamePtr->gameWindow.draw(backgroundShapeHelp);
		gamePtr->gameWindow.draw(help);

	}
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
	for (int i = 3; i >= 0; --i){
		text[i].setCharacterSize(65);
		text[i].setColor(sf::Color::White);

		text[i].setOrigin(text[i].getLocalBounds().width / 2, text[i].getLocalBounds().height / 2);

		text[i].setPosition(gamePtr->view.getCenter().x, center - 75 * i);

	}
	
	help.setOrigin(help.getLocalBounds().width / 2, help.getLocalBounds().height / 2);
	help.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);

	text[klawisz].setColor(sf::Color::Red);
	return true;

}

bool MenuState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
		if (helpPressed == false && klawisz == 3)
		{
			requestStackPop();
			requestStackPush(States::LOAD);
		}
		else if (helpPressed == false && klawisz == 1)
		{
			requestStackPush(States::OPTIONS);
		}
		else if (helpPressed == false && klawisz == 2)
		{
			helpPressed = !helpPressed;
			
		}
		else if (helpPressed == false && klawisz == 0)
		{
			exit(1);
			requestStateClear();
			gamePtr->gameWindow.close();
		}
		else helpPressed = !helpPressed;
			
	}
	else if (helpPressed == false && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
		--klawisz;
		if (klawisz < 0)
			klawisz = 3;
	}
	else if (helpPressed == false && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
		++klawisz;
		if (klawisz > 3)
			klawisz = 0;
	}
	return true;
}

//text.setPosition(gamePtr->view.getCenter().x - gamePtr->graphics.getWindowWidth()/100, gamePtr->view.getCenter().y - gamePtr->graphics.getWindowHeight()/7);
//text.setPosition((gamePtr->gameWindow.getView().getSize().x / 2) - 170,  (gamePtr->gameWindow.getView().getSize().y / 2) - 130);
//text.setPosition(gamePtr->view.getCenter().x, gamePtr->view.getCenter().y);
//text.setPosition(gamePtr->graphics.getWindowWidth() / 2, gamePtr->graphics.getWindowHeight() / 2);