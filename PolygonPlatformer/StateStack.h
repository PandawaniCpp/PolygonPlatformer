#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <cassert>
#include "State.h"
#include "ResourcesID.h"
#include "Graphics.h"



class StateStack {
public:        
	enum Action        
	{
		PUSH, 
		POP, 
		CLEAR, 
	};
public:                
	explicit	   StateStack(); 
	virtual		   ~StateStack();
	template <typename T>
	void           registerState(States::ID stateID);
	void           update(sf::Time dt);       
    void           draw (sf::RenderTarget& target);
	void           handleEvent(const sf::Event& event);
	void           pushState(States::ID stateID);        
	void           popState();        
	void           clearStates();
	bool           isEmpty() const;
	void           applyPendingChanges();
	States::ID	   getCurrentStateID();
private:     
	State::Ptr     createState(States::ID stateID);        
	
	struct PendingChange        
	{
		explicit PendingChange(Action action, States::ID stateID = States::NONE);
		Action      action;            
		States::ID  stateID; 
	};
     
	std::vector<State::Ptr>        stateStack;        
	std::vector<PendingChange>     pendingList;        
	std::map<States::ID, std::function<State::Ptr()>>    factories;
};


template <typename T> 
void StateStack::registerState(States::ID stateID) {    
	factories[stateID] = [this] ()    
	{        
		return State::Ptr(new T(*this));    
	}; 
} 