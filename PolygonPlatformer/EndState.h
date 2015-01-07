#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

class StateStack;
class EndState : public State {
public:

	EndState(StateStack & stack, Game * game);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);


private:

	sf::Text text;
	sf::Font   font;
	sf::Texture texture;
	sf::Sprite background;
	sf::Time textEffectTime;
	bool textVisible;

};