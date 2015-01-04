#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
class StateStack;
class PauseState : public State {
public:

	PauseState(StateStack & stack, Game * game);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);


private:
	SceneNode root;
	int				klawisz;
	sf::RectangleShape backgroundShape;
	sf::Text text[4];
	sf::Font   font;
};