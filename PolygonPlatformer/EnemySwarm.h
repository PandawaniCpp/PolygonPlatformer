#include "Creature.h"
#include "EnemyBullet.h"
#include "NonPhysical.h"


class EnemySwarm :public Creature{
public:
	EnemySwarm(float x, float y);
	~EnemySwarm();
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	void preSolve(b2Contact* contact, SceneNode* anotherNode);
	void beginContact(SceneNode* anotherNode);
	//void endContact(SceneNode* anotherNode);
	//Ptr healthbar_red;
	//Ptr healthbar_green;
	//void shoot();
	//sf::Time shootingCooldown;
	//sf::Time timeSinceLastShot;
	//sf::Time ghostMode;
	float currentVelocity;
	b2Vec2 pointingToPlayer;

};