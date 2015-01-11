
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
    stateStack->gameStatePtr->money = SceneNode::globalMoney;

	gamePtr->gameWindow.draw(backgroundShape);

	for (int i = 0; i < 5; ++i)
		gamePtr->gameWindow.draw(text[i]);

    stateStack->gameStatePtr->moneyString.str (std::string ());
    stateStack->gameStatePtr->moneyString.clear ();
    stateStack->gameStatePtr->moneyString << "Money: " << stateStack->gameStatePtr->money;
    stateStack->gameStatePtr->moneyCounter.setString (stateStack->gameStatePtr->moneyString.str ());
    stateStack->gameStatePtr->moneyCounter.setPosition (sf::Vector2f (gamePtr->view.getCenter ().x - (gamePtr->graphics.getWindowWidth () / 2) + 10,
        gamePtr->view.getCenter ().y + (gamePtr->graphics.getWindowHeight () / 2) - 10 - stateStack->gameStatePtr->moneyCounter.getLocalBounds ().height));
    gamePtr->gameWindow.draw (stateStack->gameStatePtr->moneyCounter);
}

bool UpgradeState::update(sf::Time dt) {
	if (SceneNode::globalMoney <= 0)
		SceneNode::globalMoney = 0;
	stateStack->gameStatePtr->helpPressed = false;
	gamePtr->view.setSize(gamePtr->graphics.getWindowWidth(), gamePtr->graphics.getWindowHeight());
	unsigned center = gamePtr->view.getCenter().y + gamePtr->graphics.getWindowHeight() / 5;

	//+std::to_string()

    text[0].setString ("Piercing Bulltes     " + std::to_string (500));
    text[1].setString ("Health               +  " + std::to_string(10+(4 + stateStack->gameStatePtr->upgradeCounter[1]+1) * 5)+"   " + std::to_string (stateStack->gameStatePtr->upgrade[0]));
    text[2].setString ("Cannibalism         +  " + std::to_string (1+((stateStack->gameStatePtr->upgradeCounter[2]+1) / 3)) + "   " + std::to_string (stateStack->gameStatePtr->upgrade[1]));
    text[3].setString ("Damage              +  " + std::to_string ((1 + stateStack->gameStatePtr->upgradeCounter[3]+1)) + "   " + std::to_string (stateStack->gameStatePtr->upgrade[2]));
    text[4].setString ("Ready");
	
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

                  if (SceneNode::globalMoney >= 500) {
                      Player::me->piercingBullets = true;
                     // choose = true;
                      SceneNode::globalMoney -= 500;
                      if (SceneNode::globalMoney <= 0)
                          SceneNode::globalMoney = 0;
                  }
			
		
                  break;
		}
		case 1:
		{
                  if (SceneNode::globalMoney >= stateStack->gameStatePtr->upgrade[0]) {
                      stateStack->gameStatePtr->upgradeCounter[1]++;
                      Player::me->maxHP = Player::me->maxHP + 10+((4 + stateStack->gameStatePtr->upgradeCounter[1])*5);
                      Player::me->currentHP = Player::me->maxHP;
                     // choose = true;
                      SceneNode::globalMoney -= stateStack->gameStatePtr->upgrade[0];
                      stateStack->gameStatePtr->upgrade[0] = stateStack->gameStatePtr->upgrade[0] +  (stateStack->gameStatePtr->upgradeCounter[1]*50);
                      
                      if (SceneNode::globalMoney <= 0)
                          SceneNode::globalMoney = 0;

                  }
			wasPressed = 1;
			
            break;
		}
		case 2:
		{

                  if (SceneNode::globalMoney >= stateStack->gameStatePtr->upgrade[1]) {
                      if (!((stateStack->gameStatePtr->upgradeCounter[2] / 3)>2))
                      stateStack->gameStatePtr->upgradeCounter[2]++;



                      Player::me->hpPerMob = Player::me->hpPerMob + 1 + (stateStack->gameStatePtr->upgradeCounter[2]/3);
                      
                     
                     // choose = true;
                      SceneNode::globalMoney -= stateStack->gameStatePtr->upgrade[1];
                      stateStack->gameStatePtr->upgrade[1] = stateStack->gameStatePtr->upgrade[1] +40+  (stateStack->gameStatePtr->upgradeCounter[2] * 50);
                      if (SceneNode::globalMoney <= 0)
                          SceneNode::globalMoney = 0;
                    
                  }
			wasPressed = 2;
			
            break;
		}
		case 3:
		{
                  if (SceneNode::globalMoney >= (stateStack->gameStatePtr->upgrade[2])) {
                      if (!((1 + stateStack->gameStatePtr->upgradeCounter[3])>9))
                      stateStack->gameStatePtr->upgradeCounter[3]++;
                      Player::me->bulletDamageVar = Player::me->bulletDamageVar + (1 + stateStack->gameStatePtr->upgradeCounter[3]);
                     
                    
                      //choose = true;
                      SceneNode::globalMoney -= stateStack->gameStatePtr->upgrade[2];
                      stateStack->gameStatePtr->upgrade[2] = stateStack->gameStatePtr->upgrade[2] +20+ (stateStack->gameStatePtr->upgradeCounter[3] * 50);
                      if (SceneNode::globalMoney < 0)
                          SceneNode::globalMoney = 0;
                  }
			wasPressed = 3;
			
            break;
		}
		case 4:
		{
			
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