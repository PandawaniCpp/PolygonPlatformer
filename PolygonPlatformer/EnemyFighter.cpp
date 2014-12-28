#include "EnemyFighter.h"

#define PIXELTOMETER (1.f/10.f)




EnemyFighter::~EnemyFighter(){
	globalWorld->DestroyBody(myBody);
}






EnemyFighter::EnemyFighter(float x, float y) :healthbar_red(new SceneNode), healthbar_green(new SceneNode){

	MyId = ObjectId::ENEMY_FIGHTER;

	maxHP = 20;
	currentHP = 20;


	setTexture(globalTextureHolder->get(Textures::ENEMY_FIGHTER));
	setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f);
	globalRoot->attachChild(Ptr(this));

	b2FixtureDef boxFixtureDef;
	b2PolygonShape boxShape;
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(x*PIXELTOMETER, y*PIXELTOMETER);
	myBodyDef.angle = 0;
	b2Body* dynamicBody = globalWorld->CreateBody(&myBodyDef);
	boxShape.SetAsBox((getTextureRect().width / 2.f)*PIXELTOMETER, (getTextureRect().height / 2.f)*PIXELTOMETER);
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxFixtureDef.friction = 0;
	dynamicBody->CreateFixture(&boxFixtureDef);
	dynamicBody->SetFixedRotation(true);
	dynamicBody->SetUserData(this);
	myBody = dynamicBody;



	/*textures->load(Textures::HEALTHBAR_RED, "./textures/healthbar_red.png");
	textures->load(Textures::HEALTHBAR_GREEN, "./textures/healthbar_green.png");*/
	healthbar_red->setTexture(globalTextureHolder->get(Textures::HEALTHBAR_RED));
	healthbar_green->setTexture(globalTextureHolder->get(Textures::HEALTHBAR_GREEN));
	healthbar_red->setPosition(getPosition().x, getPosition().y - 30.f);
	healthbar_green->setPosition(getPosition().x, getPosition().y - 30.f);
	attachChild(healthbar_red);
	attachChild(healthbar_green);
	healthbar_green->setOrigin(healthbar_green->getTextureRect().width / 2.f, healthbar_green->getTextureRect().height / 2.f);
	healthbar_red->setOrigin(healthbar_red->getTextureRect().width / 2.f, healthbar_red->getTextureRect().height / 2.f);


}


void EnemyFighter::updateCurrent(sf::Time dt, b2World* world){

	if (currentHP <= 0)
	{
		globalQueuedForDeletion->push_back(this);
		return;
	}

	setPosition(myBody->GetPosition().x / PIXELTOMETER, myBody->GetPosition().y / PIXELTOMETER);



	healthbar_red->setPosition(myBody->GetPosition().x / PIXELTOMETER, (myBody->GetPosition().y / PIXELTOMETER) - 30.f);
	healthbar_green->setPosition(myBody->GetPosition().x / PIXELTOMETER, (myBody->GetPosition().y / PIXELTOMETER) - 30.f);
	healthbar_green->setTextureRect(sf::IntRect(0, 0, static_cast<int>(25 * (currentHP / maxHP)), 4));
	if (currentHP < 0)
		currentHP = 0;

	if (currentPlayer->myBody->GetPosition().x < myBody->GetPosition().x)
	{
		myBody->SetLinearVelocity(b2Vec2(-15.f, myBody->GetLinearVelocity().y));
	}
	else
	{
		myBody->SetLinearVelocity(b2Vec2(15.f, myBody->GetLinearVelocity().y));
	}


}



void EnemyFighter::beginContact(SceneNode* anotherNode)
{
	if (anotherNode->MyId == ObjectId::FRIENDLY_BULLET)
		damage(10);
}


void EnemyFighter::endContact(SceneNode* anotherNode)
{
	
}