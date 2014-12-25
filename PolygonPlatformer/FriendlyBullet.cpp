#include "FriendlyBullet.h"

#define PIXELTOMETER (1.f/10.f)



FriendlyBullet::~FriendlyBullet(){
	//globalWorld->DestroyBody(myBody);
	//globalRoot->detachChild(*this);
	
}




FriendlyBullet::FriendlyBullet(b2World *world, TextureHolder *texture, float positionX, float positionY, SceneNode *root){
	height = positionY;

	MyId = ObjectId::FRIENDLY_BULLET;
	velocity = 70.f;
	globalRoot = root;
	//globalRoot->detachChild(*this);
	globalWorld = world;
	globalTextureHolder = texture;
	setTexture(texture->get(Textures::FRIENDLY_BULLET));
	setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f);
	deleteIt = false;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(positionX*PIXELTOMETER,positionY*PIXELTOMETER);
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

	//myBody->SetTransform(b2Vec2(positionX*PIXELTOMETER, positionY*PIXELTOMETER),0.f);
	
	//globalRoot->attachChild();

}



void FriendlyBullet::beginContact(SceneNode* another){
	if (another->MyId != ObjectId::PLAYER)
	deleteIt = true;
}

void FriendlyBullet::updateCurrent(sf::Time dt, b2World* world){
	if (deleteIt)
	{
		//globalRoot->detachChild(*this);
		//globalWorld->DestroyBody(myBody);
		//delete this;
		//deleteIt = false;
		//setPosition(0.f, 0.f);
		//return;
	}
	myBody->SetTransform(b2Vec2(myBody->GetPosition().x, height * PIXELTOMETER), 0.f);
	myBody->SetLinearVelocity(b2Vec2(velocity, 0.f));
	setPosition(myBody->GetPosition().x / PIXELTOMETER, myBody->GetPosition().y / PIXELTOMETER);

}