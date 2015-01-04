#include "EnemySwarm.h"

#define PIXELTOMETER (1.f/10.f)
#define RADIANTODEGREE 57.2957795f
#define DEGREETORADIAN 0.0174532925f


EnemySwarm::~EnemySwarm(){
	globalWorld->DestroyBody(myBody);

	--swarmOnMap;

}






EnemySwarm::EnemySwarm(float x, float y){

	++kamikazeOnMap;


	MyId = ObjectId::ENEMY_SWARM;

	maxHP = 1;
	currentHP = 1;
	currentVelocity = 0.5f;


	setTexture(globalTextureHolder->get(Textures::ENEMY_SWARM));
	setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f);
	globalQueuedForInsertion->push_back(Ptr(this));

	//globalRoot->attachChild(Ptr(this));

	b2FixtureDef boxFixtureDef;
	b2PolygonShape boxShape;
	b2BodyDef myBodyDef;
	myBodyDef.gravityScale = 0.f;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set((x + (rand() % 40) - 20.f)*PIXELTOMETER, (y + (rand() % 40) - 20.f)*PIXELTOMETER);
	myBodyDef.angle = 0;
	b2Body* dynamicBody = globalWorld->CreateBody(&myBodyDef);
	boxShape.SetAsBox((getTextureRect().width / 2.f)*PIXELTOMETER, (getTextureRect().height / 2.f)*PIXELTOMETER);
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxFixtureDef.friction = 0;
	dynamicBody->CreateFixture(&boxFixtureDef);
	//dynamicBody->SetFixedRotation(true);
	dynamicBody->SetUserData(this);
	myBody = dynamicBody;



	/*textures->load(Textures::HEALTHBAR_RED, "./textures/healthbar_red.png");
	textures->load(Textures::HEALTHBAR_GREEN, "./textures/healthbar_green.png");*/



}




void EnemySwarm::updateCurrent(sf::Time dt, b2World* world){

	currentVelocity *= 1.01;
	if (currentVelocity >= 20.f)
		currentVelocity = 20.f;


	pointingToPlayer.x = currentPlayer->getPosition().x - getPosition().x;
	pointingToPlayer.y = currentPlayer->getPosition().y - getPosition().y;
	pointingToPlayer.Normalize();
	
	myBody->SetTransform(b2Vec2(myBody->GetPosition()),atan(pointingToPlayer.y/pointingToPlayer.x));


	pointingToPlayer *= currentVelocity;


	pointingToPlayer.x += rand() % 30 - 15.f;
	pointingToPlayer.y += rand() % 30 - 15.f;


	myBody->SetLinearVelocity(pointingToPlayer);


	if (currentHP <= 0)
	{
		soundPlayer->play(SoundEffect::ENEMY_DIES);
		globalQueuedForDeletion->push_back(this);
		/*SceneNode *tmp;
		tmp = new NonPhysical(Textures::ENEMY_FIGHTER, sf::IntRect(0, 25, 30, 25), 0, 0, 0, getPosition().x, getPosition().y + 13, 50, 0);
		globalQueuedForInsertion->push_back(Ptr(tmp));
		tmp = new NonPhysical(Textures::ENEMY_FIGHTER, sf::IntRect(0, 0, 30, 25), ((rand() % 200) / 100.f) - 1.f, ((rand() % 200) / 100.f) - 2.f, (rand() % 20) - 10.f, getPosition().x, getPosition().y - 13, 50);
		globalQueuedForInsertion->push_back(Ptr(tmp));*/
		//return;
	}

	setPosition(myBody->GetPosition().x / PIXELTOMETER, myBody->GetPosition().y / PIXELTOMETER);
	setRotation(myBody->GetAngle()*RADIANTODEGREE);


	
	if (currentHP < 0)
		currentHP = 0;

	


}



void EnemySwarm::beginContact(SceneNode* anotherNode)
{
	if (anotherNode->MyId == ObjectId::FRIENDLY_BULLET) {
		soundPlayer->play(SoundEffect::ENEMY_HIT);
		damage(10);
		SceneNode *tmp;
		if (anotherNode->myBody->GetLinearVelocity().x<0)
		tmp = new NonPhysical(Textures::ENEMY_SWARM, sf::IntRect(0, 0, 10, 10), (rand() % 100) / 10 - 10.f, (rand() % 100) / 10 - 5.f, rand() % 20 - 10.f, getPosition().x, getPosition().y, 40);
		else
			tmp = new NonPhysical(Textures::ENEMY_SWARM, sf::IntRect(0, 0, 10, 10), (rand() % 100) / 10, (rand() % 100) / 10 - 5.f, rand() % 20 - 10.f, getPosition().x, getPosition().y, 40);
		globalQueuedForInsertion->push_back(Ptr(tmp));
	}
	if (anotherNode->MyId == ObjectId::PLAYER) {
		//soundPlayer->play(SoundEffect::ENEMY_HIT);
		damage(10);
	}
}



void EnemySwarm::preSolve(b2Contact* contact, SceneNode* anotherNode){

	if (anotherNode->MyId == ObjectId::ENEMY_SWARM)
		return;


	if (anotherNode->MyId != ObjectId::PLAYER)
		contact->SetEnabled(false);
}