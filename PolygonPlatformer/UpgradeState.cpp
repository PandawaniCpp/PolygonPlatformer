
#include "UpgradeState.h"


UpgradeState::UpgradeState(StateStack & stack, Game * game)
	: State(stack, game) {

	stateID = States::UPGRADE;
	klawisz = 4;
	wasPressed = 4;
	choose = false;

	for (int i = 0; i < 5; i++){
		text[i].setStyle(sf::Text::Bold);
		text[i].setFont(font);
	}
	font.loadFromFile("./textures/coolFont.ttf");
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(10000, 10000));

}

void UpgradeState::draw(sf::RenderTarget& target) {

	gamePtr->gameWindow.draw(backgroundShape);
	for (int i = 0; i < 5; ++i)
		gamePtr->gameWindow.draw(text[i]);
}

bool UpgradeState::update(sf::Time dt) {
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	unsigned center = gamePtr->view.getCenter().y + gamePtr->graphics.getWindowHeight() / 5;

	//+std::to_string()
	text[0].setString("Piercing Bulltes");
	text[1].setString("Health");
	text[2].setString("Wysys hp z moba");
	text[3].setString("Damage");
	text[4].setString("Ready");

	for (int i = 4; i >= 0; --i)
	{
		text[i].setCharacterSize(45);
		text[i].setColor(sf::Color::White);
		text[i].setOrigin(text[i].getLocalBounds().width / 2, text[i].getLocalBounds().height / 2);
		text[i].setPosition(gamePtr->view.getCenter().x, center - 50 * i);

	}
	if (choose)
		text[wasPressed].setColor(sf::Color::Blue);
	text[klawisz].setColor(sf::Color::Red);

	if (Player::me->piercingBullets)
		text[0].setColor(sf::Color::Green);
	return true;
}

bool UpgradeState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
		switch (klawisz){
		case 0:
		{
			wasPressed = 0;
			choose = true;
			break;
		}
		case 1:
		{

			wasPressed = 1;
			choose = true;
			break;
		}
		case 2:
		{
			wasPressed = 2;
			choose = true;
			break;
		}
		case 3:
		{

			wasPressed = 3;
			choose = true;
			break;
		}
		case 4:
		{
			switch (wasPressed)
			{
			case 0: Player::me->piercingBullets = true; choose = true; break;
			case 1: Player::me->maxHP = Player::me->maxHP*1.2; choose = true; break;
			case 2: choose = true; break;
			case 3:Player::me->bulletDamageVar = Player::me->bulletDamageVar*1.3; choose = true; break;
			default:
				break;
			}

			requestStackPop();
		}
			break;
		}
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){

		--klawisz;
		if (!Player::me->piercingBullets)
		{
			if (klawisz < 0)
				klawisz = 4;
		}
		else if (klawisz < 1)
			klawisz = 4;
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){

		++klawisz;
		if (!Player::me->piercingBullets)
		{
			if (klawisz > 4)
				klawisz = 0;
		}
		else if (klawisz>4)
			klawisz = 1;
	}
	return true;

}

/*
Wrzuc sobie tam gdzie Ci pasuje wywolanie Upgradew GameState
zwykly if(){
requestStackPush (States::UPGRADE);
}
i masz na stosie stan Upgrade, i od razu sie zalacza;
jak chcesz wrócic do poprzedniego robisz po prostu
gdzies w Upgrade

requestStackPop();

i wraca do poprzedniego stanu
*/