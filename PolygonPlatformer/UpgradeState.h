#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

class StateStack;


	
	enum button
	{
		BUTTON1=0,
		BUTTON2,
		BUTTON3,
		BUTTON4,
		BUTTON5,
	};

class UpgradeState : public State {
public:

	UpgradeState(StateStack & stack, Game * game);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);


private:
	//gamePtr
	SceneNode root;
	TextureHolder buttons;
	button			whichButton;
	int				klawisz;
	sf::RectangleShape backgroundShape;
	sf::Text text[5];
	sf::Font   font;

};