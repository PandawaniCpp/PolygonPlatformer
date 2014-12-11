#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "ResourcesID.h"

//#include "../ResourceHolder.h"
//#include "../Command.h"


class StateStack;

//CONTEXT!!
class State {
public:        
	typedef std::unique_ptr <State> Ptr;        
    
	State();
	State(StateStack& stack);
	virtual         ~State();						   
	virtual void    draw() = 0;        
	virtual bool    update(sf::Time dt) = 0;        
	virtual bool    handleEvent(const sf::Event& event)=0;
	States::ID		getStateID();
	//Game *			getGame() const;
protected:        
	void            requestStackPush(States::ID stateID);       
	void            requestStackPop();        
	void            requestStateClear(); 
	//Game *			game;
	// State's ID. Needed for key mapping interpretation.
	States::ID stateID;
	StateStack*     stateStack;
private:       
	       
	//Context         mContext;
};
