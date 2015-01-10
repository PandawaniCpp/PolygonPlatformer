#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

class StateStack;
class MenuState : public State {
public:

	enum OptionNames { Play, Options, Exit, };


	MenuState(StateStack & stack, Game * game);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	// HELP
	sf::Text help;
	sf::Sprite backgroundHelp;
	sf::Texture textureHelp;
	bool      helpPressed;
	sf::RectangleShape backgroundShapeHelp;

private:
	int				klawisz;
	sf::Text text[4];
	sf::Font   font;
	sf::Texture texture;
	sf::Sprite background;
	sf::Time textEffectTime;


};