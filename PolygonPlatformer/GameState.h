#pragma once
#include "State.h"
#include "Player.h"
#include "Creature.h"
#include "EnemyFighter.h"
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <Box2D/Box2D.h>
#include "Map.h"
#include "MyContactListener.h"
#include "MusicPlayer.h"
#include "Game.h"
#include "SoundPlayer.h"

class StateStack;
class GameState : public State{
public:
	
	GameState(StateStack & stack, Game * gamePtr);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);  
    /*void createBot ();*/
	void spawnEnemyFighter(float x, float y);

private:
	SceneNode*	player;
    SceneNode * map;
    SceneNode root;
    TextureHolder textures;
	SoundPlayer soundPlayer;
    b2Vec2 gravity;
    bool doSleep;
    b2World *world;
    float timeStep;
    int velocityIterations;
    int positionIterations;
    b2BodyDef groundBodyDef;
    b2PolygonShape groundBox;
	MyContactListener myContactListenerInstance;
	std::vector<SceneNode *> queuedForDeletion;
	std::vector<SceneNode::Ptr> queuedForInsertion;
	//Window View
	sf::View view;


};