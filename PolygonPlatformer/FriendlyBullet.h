#include "SceneNode.h"
#include "TextureHolder.h"
#include "NonPhysical.h"


class FriendlyBullet : public SceneNode{
public:
	FriendlyBullet(float positionX, float positionY, bool facingRight);
	~FriendlyBullet();
	void beginContact(SceneNode* anotherNode);
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	float velocity;
	float height;
	int current_direction;
};