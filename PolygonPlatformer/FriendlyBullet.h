#include "SceneNode.h"
#include "TextureHolder.h"


class FriendlyBullet : public SceneNode{
public:
	FriendlyBullet(b2World *world, TextureHolder *texture, float positionX, float positionY,SceneNode *root);
	~FriendlyBullet();
	void beginContact(SceneNode* anotherNode);
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	float velocity;
	bool deleteIt;
	float height;
};