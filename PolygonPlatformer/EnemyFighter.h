#include "Creature.h"

class EnemyFighter :public Creature{
public:
	EnemyFighter(float x, float y);
	~EnemyFighter();
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	void beginContact(SceneNode* anotherNode);
	void endContact(SceneNode* anotherNode);
	Ptr healthbar_red;
	Ptr healthbar_green;


};