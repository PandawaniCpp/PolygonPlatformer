#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>

class StateStack;
class TitleState : public State {
public:

	TitleState(StateStack & stack);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);


private:
	SceneNode root;

	TextureHolder backgroundMenu;

};