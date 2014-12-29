#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <memory>
#include "ResourcesID.h"
#include "SceneNode.h"

class StateStack;
class Game;
class State {
public:        
	typedef std::unique_ptr <State> Ptr;        
	 	
	State(StateStack& stack, Game *game);
	virtual         ~State();						   
    virtual void    draw (sf::RenderTarget& target) = 0;
	virtual bool    update(sf::Time dt) = 0;        
	virtual bool    handleEvent(const sf::Event& event);
	States::ID		getStateID();
	Game*			gamePtr;
protected:        
	void            requestStackPush(States::ID stateID);       
	void            requestStackPop();        
	void            requestStateClear(); 
	

	States::ID stateID;
	StateStack*     stateStack;

};
