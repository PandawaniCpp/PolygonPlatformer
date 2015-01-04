#include "Creature.h"
#include "EnemyBullet.h"
#include "NonPhysical.h"


class EnemyKamikaze :public Creature{
public:
	EnemyKamikaze(float x, float y);
	~EnemyKamikaze();
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	void preSolve(b2Contact* contact, SceneNode* anotherNode);
	void beginContact(SceneNode* anotherNode);
	//void endContact(SceneNode* anotherNode);
	Ptr healthbar_red;
	Ptr healthbar_green;
	//void shoot();
	//sf::Time shootingCooldown;
	//sf::Time timeSinceLastShot;
	sf::Time ghostMode;
	bool destroyedOnContact;

};