
#include "UpgradeState.h"


UpgradeState::UpgradeState(StateStack & stack, Game * game)
	: State(stack, game) {
	stateID = States::UPGRADE;	
	whichButton = BUTTON1;
	klawisz = 0;
	/*buttons.load(Textures::BUTTON1, "./textures/button1.png");
	buttons.load(Textures::BUTTON2, "./textures/button2.png");
	buttons.load(Textures::BUTTON3, "./textures/button3.png");
	buttons.load(Textures::BUTTON4, "./textures/button4.png");
	buttons.load(Textures::BUTTON5, "./textures/button5.png");
	
	SceneNode::Ptr tmp(new SceneNode);
	tmp->setTexture(buttons.get(Textures::UPGRADE));
	root.attachChild(tmp);*/

	font.loadFromFile("./textures/coolFont.ttf");
	for (int i = 0; i < 5; i++){
		text[i].setStyle(sf::Text::Bold);
		text[i].setColor(sf::Color::Red);
		text[i].setFont(font);
	}
	text[0].setString("Ddamadż");
	text[1].setString("Helth");
	text[2].setString("Wysys hp z moba");
	text[3].setString("Kulki");
	text[4].setString("Ready");
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(10000, 10000));

}

void UpgradeState::draw(sf::RenderTarget& target) {

	gamePtr->gameWindow.draw(backgroundShape);
	for (int i = 0; i < 5;++i)
	gamePtr->gameWindow.draw(text[i]);
}

bool UpgradeState::update(sf::Time dt) {
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	for (int i = 0; i < 5; i++){
		text[i].setCharacterSize(45);
		text[i].setColor(sf::Color::White);

		text[i].setOrigin(text[i].getLocalBounds().width / 2, text[i].getLocalBounds().height / 2);

		text[i].setPosition(gamePtr->view.getCenter().x, (gamePtr->graphics.getWindowHeight()/8)+100*i);

	}
	text[klawisz].setColor(sf::Color::Red);
	return true;
}

bool UpgradeState::handleEvent(const sf::Event& event) {
	
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
		requestStackPop();
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
		++klawisz;
		if (klawisz >4)
			klawisz = 0;
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
		--klawisz;
		if (klawisz < 0)
			klawisz = 4;
	}
	return true;
	/*
	Wrzuć sobie tam gdzie Ci pasuje wywołanie Upgradew GameState
	zwykły if(){
	requestStackPush (States::UPGRADE);
	}
	i masz na stosie stan Upgrade, i od razu się załącza;
	jak chcesz wrócić do poprzedniego robisz po prostu
	gdzieś w Upgrade

	requestStackPop();
	
	i wraca do poprzedniego stanu
	*/
	return true;
}
