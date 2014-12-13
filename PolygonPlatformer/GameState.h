#include "State.h"
#include <SFML/Graphics.hpp>

class StateStack;
class GameState : public State {
public:
	
	GameState(StateStack & stack);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event) = 0;  

private:
	//Player&			player;
	//World           world;
};