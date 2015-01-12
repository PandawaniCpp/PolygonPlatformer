#include "Creature.h"
#include "EnemyBullet.h"
#include "NonPhysical.h"
#include "Pickup.h"


class EnemyFighter :public Creature{
public:
	EnemyFighter(float x, float y);
	~EnemyFighter();
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	void preSolve(b2Contact* contact, SceneNode* anotherNode);
	void beginContact(SceneNode* anotherNode);
	void endContact(SceneNode* anotherNode);
	Ptr healthbar_red;
	Ptr healthbar_green;
	void shoot();
	sf::Time shootingCooldown;
	sf::Time timeSinceLastShot;
	sf::Time ghostMode;

};