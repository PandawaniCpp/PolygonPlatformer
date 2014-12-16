#pragma once
#include "State.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <Box2D/Box2D.h>
#include "Platform.h"

class StateStack;
class GameState : public State{
public:
	
	GameState(StateStack & stack);

	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);  

private:
	Player::Ptr	player;
    SceneNode root;
    TextureHolder textures;
    b2Vec2 gravity;
    bool doSleep;
    b2World *world;
    float timeStep;
    int velocityIterations;
    int positionIterations;
    b2FixtureDef boxFixtureDef;
    b2PolygonShape boxShape;
    b2BodyDef myBodyDef;
    b2BodyDef groundBodyDef;
    b2PolygonShape groundBox;


};