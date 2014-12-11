#include "State.h"
#include <SFML/Graphics.hpp>

class StateStack;
class MenuState : public State {
public:
	// Constructor.
	MenuState(StateStack & stack);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event)=0;  //COMMAND


private:
	sf::Text text;
	sf::Texture texture;
	sf::Sprite background;

};