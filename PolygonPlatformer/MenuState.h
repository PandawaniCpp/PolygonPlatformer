#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

class StateStack;
class MenuState : public State {
public:
	
	MenuState(StateStack & stack, Game * game);

    virtual void draw (sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event); 


private:
	SceneNode root;
	sf::RectangleShape backgroundShape;
	sf::Text text;
	sf::Font   font;

};