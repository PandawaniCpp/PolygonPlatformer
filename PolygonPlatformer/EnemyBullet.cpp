#include "EnemyBullet.h"

#define PIXELTOMETER (1.f/10.f)



EnemyBullet::~EnemyBullet(){
	globalWorld->DestroyBody(myBody);

}




EnemyBullet::EnemyBullet(float positionX, float positionY, bool facingRight){
	height = positionY;
	MyId = ObjectId::ENEMY_BULLET;

	if (facingRight)
		current_direction = 1;
	else current_direction = -1;
	velocity = 70.f*current_direction;

	setTexture(globalTextureHolder->get(Textures::ENEMY_BULLET));
	setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f);

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set((positionX + (20.f*current_direction))*PIXELTOMETER, positionY*PIXELTOMETER);
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



void EnemyBullet::beginContact(SceneNode* another){
    needsToGetDeleted = true;
    if (another->MyId == ObjectId::ENEMY_FIGHTER || another->MyId == ObjectId::ENEMY_FAT || another->MyId == ObjectId::ENEMY_SWARM || another->MyId == ObjectId::ENEMY_KAMIKAZE)
		//globalQueuedForDeletion->push_back(this);
		needsToGetDeleted = false;
	if (another->MyId == ObjectId::PLAYER)
	{
		SceneNode *tmp;
		int size;
		for (int i = (rand() % 7) - 3; i < 9; ++i)
		{
			size = rand() % 5;
			tmp = new NonPhysical(Textures::BLOOD, sf::IntRect(0, 0, size, size), ((rand() % 200) / 100.f) - 1.f, ((rand() % 200) / 100.f) - 1.f, 20, getPosition().x, getPosition().y, 80);
			globalQueuedForInsertion->push_back(Ptr(tmp));
		}

	}
}

void EnemyBullet::preSolve(b2Contact* contact, SceneNode* anotherNode){
	if (anotherNode->MyId == ObjectId::ENEMY_FIGHTER)
		contact->SetEnabled(false);
}





void EnemyBullet::updateCurrent(sf::Time dt, b2World* world){
	if (needsToGetDeleted)
	{
		globalQueuedForDeletion->push_back(this);
		return;
	}


	myBody->SetTransform(b2Vec2(myBody->GetPosition().x, height * PIXELTOMETER), 0.f);
	myBody->SetLinearVelocity(b2Vec2(velocity, 0.f));
	setPosition(myBody->GetPosition().x / PIXELTOMETER, myBody->GetPosition().y / PIXELTOMETER);

}