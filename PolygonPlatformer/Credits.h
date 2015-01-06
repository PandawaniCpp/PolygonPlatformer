#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

class StateStack;
class Credits : public State {
public:

	Credits(StateStack & stack, Game * game);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	float			x;
	float			y;

private:

	sf::Text text[5];
	sf::Font   font;
	sf::Texture texture;
	sf::Sprite background;
	sf::Time textEffectTime;
	bool textVisible;

};