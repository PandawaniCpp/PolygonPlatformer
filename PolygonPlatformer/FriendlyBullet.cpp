#include "FriendlyBullet.h"

#define PIXELTOMETER (1.f/10.f)



FriendlyBullet::~FriendlyBullet(){
	globalWorld->DestroyBody(myBody);
	
}




FriendlyBullet::FriendlyBullet(b2World *world, TextureHolder *texture, float positionX, float positionY, SceneNode *root, std::vector<SceneNode *> *queued, bool facingRight){
	height = positionY;
	globalQueuedForDeletion = queued;
	MyId = ObjectId::FRIENDLY_BULLET;
	//velocity = 70.f;
	globalRoot = root;
	if (facingRight)
		current_direction = 1;
	else current_direction = -1;
	velocity = 70.f*current_direction;

	globalWorld = world;
	globalTextureHolder = texture;
	setTexture(texture->get(Textures::FRIENDLY_BULLET));
	setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f);

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set((positionX+(20.f*current_direction))*PIXELTOMETER,positionY*PIXELTOMETER);
	myBodyDef.angle = 0;

	b2Body* dynamicBody = globalWorld->CreateBody(&myBodyDef);

	b2PolygonShape boxShape;

	boxShape.SetAsBox((getTextureRect().width / 2.f)*PIXELTOMETER, (getTextureRect().height / 2.f)*PIXELTOMETER);
	
	b2FixtureDef boxFixtureDef;

	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxFixtureDef.friction = 0;
	dynamicBody->CreateFixture(&boxFixtureDef);
	dynamicBody->SetFixedRotation(true);
	dynamicBody->SetUserData(this);
	myBody = dynamicBody;

}



void FriendlyBullet::beginContact(SceneNode* another){
	if (another->MyId != ObjectId::PLAYER)
		globalQueuedForDeletion->push_back(this);
}

void FriendlyBullet::updateCurrent(sf::Time dt, b2World* world){
	
	myBody->SetTransform(b2Vec2(myBody->GetPosition().x, height * PIXELTOMETER), 0.f);
	myBody->SetLinearVelocity(b2Vec2(velocity, 0.f));
	setPosition(myBody->GetPosition().x / PIXELTOMETER, myBody->GetPosition().y / PIXELTOMETER);

}