#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Player.h"
class StateStack;
class UpgradeState : public State {
public:

	UpgradeState(StateStack & stack, Game * game);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);


private:
	
	SceneNode root;
	int				klawisz;
	int				wasPressed;
	bool			choose;
	sf::RectangleShape backgroundShape;
	sf::Text text[5];
	sf::Font   font;

};