#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <memory>
#include "ResourcesID.h"

class StateStack;

class State {
public:        
	typedef std::unique_ptr <State> Ptr;        
	 	
	State();
	State(StateStack& stack, sf::RenderWindow* ptr);
	virtual         ~State();						   
    virtual void    draw (sf::RenderTarget& target) = 0;
	virtual bool    update(sf::Time dt) = 0;        
	virtual bool    handleEvent(const sf::Event& event);
	States::ID		getStateID();
	
protected:        
	void            requestStackPush(States::ID stateID);       
	void            requestStackPop();        
	void            requestStateClear(); 
	

	States::ID stateID;
	StateStack*     stateStack;
	sf::RenderWindow*  ptrWindow;

	

};
