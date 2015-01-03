#include "Creature.h"
#include "EnemyBullet.h"
#include "NonPhysical.h"


class EnemyFat :public Creature{
public:
	EnemyFat(float x, float y);
	~EnemyFat();
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	//void preSolve(b2Contact* contact, SceneNode* anotherNode);
	void beginContact(SceneNode* anotherNode);
	void endContact(SceneNode* anotherNode);
	Ptr healthbar_red;
	Ptr healthbar_green;
	void jump();
	sf::Time jumpingCooldown;
	sf::Time timeSinceLastJump;
	//sf::Time ghostMode;

};