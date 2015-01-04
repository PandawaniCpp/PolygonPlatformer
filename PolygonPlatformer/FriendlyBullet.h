#include "SceneNode.h"
#include "TextureHolder.h"
#include "NonPhysical.h"


class FriendlyBullet : public SceneNode{
public:
	FriendlyBullet(float positionX, float positionY, bool facingRight, bool isPiercingArg, float bulletDamageArg);
	~FriendlyBullet();
	void beginContact(SceneNode* anotherNode);
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	virtual float getDamage(){
		return bulletDamage;
	}
	float velocity;
	float height;
	int current_direction;
	bool isPiercing;
	float bulletDamage;
};