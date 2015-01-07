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
#include "EnemyFat.h"
#include "EnemySwarm.h"
#include "EnemyKamikaze.h"

class StateStack;
class GameState : public State{
public:
	
	GameState(StateStack & stack, Game * gamePtr);
	virtual			~GameState();
	virtual void draw(sf::RenderTarget& target);
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);  
    /*void createBot ();*/
	void spawnEnemyFighter(float x, float y);
	void spawnEnemyFat(float x, float y);
	void spawnEnemySwarm(float x, float y);
	void spawnEnemyKamikaze(float x, float y);

	void setEnemiesOnMap(unsigned int number);
	unsigned int getEnemiesOnMap();
	SceneNode*	player;

	// HELP
	sf::Text help;
	sf::Sprite background;
	sf::Texture texture;
	bool      helpPressed;
	sf::RectangleShape backgroundShape;
	
	unsigned		upgrade[3];
	unsigned		money;
    sf::Time spawnCooldown;
    sf::Text moneyCounter;

	unsigned int enemiesNumber;
	sf::Font font;
	sf::Text enemiesCounter;
	
	std::ostringstream enemiesOnMap;
	std::ostringstream moneyString;

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
	int fighterToSpawn;
	int fatToSpawn;
	int kamikazeToSpawn;
	int swarmToSpawn;

    SceneNode * gameBackground;


};