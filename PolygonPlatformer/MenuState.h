#include "State.h"
#include <SFML/Graphics.hpp>

class StateStack;
class MenuState : public State {
public:
	
	MenuState(StateStack & stack);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event)=0; 


private:
	       
	TextureHolder backgroundMenu;

};