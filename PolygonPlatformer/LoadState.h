#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

class StateStack;
class LoadState : public State {
public:

	
	LoadState(StateStack & stack, Game * game);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	// HELP

	sf::RectangleShape backgroundShapeHelp;

private:
	
	sf::Text text;
	sf::Font   font;
	sf::Texture texture;
	sf::Sprite background;
	sf::Time textEffectTime;


};