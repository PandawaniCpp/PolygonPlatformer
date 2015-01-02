
#include "UpgradeState.h"


UpgradeState::UpgradeState(StateStack & stack, Game * game)
	: State(stack, game) {
	stateID = States::UPGRADE;	
}

void UpgradeState::draw(sf::RenderTarget& target) {
	
}

bool UpgradeState::update(sf::Time dt) {
	return true;
}

bool UpgradeState::handleEvent(const sf::Event& event) {
	
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
