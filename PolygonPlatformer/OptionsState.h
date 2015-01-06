#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

class StateStack;
class OptionsState : public State {
public:

	OptionsState(StateStack & stack, Game * game);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	
private:
	int				klawisz;
	int				risk;
	bool			isCute;
	sf::Text text[4];
	sf::Font   font;
	sf::Texture texture;
	sf::Texture	cute;
	sf::Sprite background;
	sf::Time textEffectTime;

};