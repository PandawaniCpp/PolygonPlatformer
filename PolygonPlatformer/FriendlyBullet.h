#include "SceneNode.h"
#include "TextureHolder.h"


class FriendlyBullet : public SceneNode{
public:
	FriendlyBullet(b2World *world, TextureHolder *texture, float positionX, float positionY, SceneNode *root, std::vector<SceneNode *> *queued, bool facingRight);
	~FriendlyBullet();
	void beginContact(SceneNode* anotherNode);
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	float velocity;
	float height;
	int current_direction;
};