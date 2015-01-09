#include "EnemyFighter.h"
#include "Player.h"
#define PIXELTOMETER (1.f/10.f)




EnemyFighter::~EnemyFighter(){
	globalWorld->DestroyBody(myBody);
	--fighterOnMap;
	Player::me->heal(Player::me->hpPerMob);

    globalMoney += 8 + (2 * currentWave);

}






EnemyFighter::EnemyFighter(float x, float y) :healthbar_red(new SceneNode), healthbar_green(new SceneNode){

	++fighterOnMap;


	MyId = ObjectId::ENEMY_FIGHTER;

	maxHP = 20;

    for (int k = 0; k < SceneNode::currentWave - 1; ++k)
        maxHP +=   k;

	currentHP = maxHP;
	shootingCooldown = sf::seconds(1);
	timeSinceLastShot = sf::Time::Zero;
	ghostMode = sf::Time::Zero;


	setTexture(globalTextureHolder->get(Textures::ENEMY_FIGHTER));
	setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f);
	globalQueuedForInsertion->push_back(Ptr(this));

	//globalRoot->attachChild(Ptr(this));

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

void EnemyFighter::shoot()
{
	SceneNode::Ptr tmp(new EnemyBullet((myBody->GetPosition().x / PIXELTOMETER), myBody->GetPosition().y / PIXELTOMETER, (myBody->GetPosition().x<currentPlayer->myBody->GetPosition().x) ? true : false));

	globalQueuedForInsertion->push_back(tmp);
}


void EnemyFighter::updateCurrent(sf::Time dt, b2World* world){

    if (getPosition ().y >=6000)
        damage (maxHP);

	ghostMode -= dt;
	if (ghostMode <= sf::Time::Zero)
		ghostMode = sf::Time::Zero;
	if (ghostMode <= sf::Time::Zero&&myBody->GetPosition().y < currentPlayer->myBody->GetPosition().y && (myBody->GetPosition().x - currentPlayer->myBody->GetPosition().x >-0.5f && myBody->GetPosition().x - currentPlayer->myBody->GetPosition().x <0.5f))
		ghostMode = sf::seconds(1.f/3.f);
	

	if ((myBody->GetLinearVelocity().y==0)&&ghostMode <= sf::Time::Zero&&myBody->GetPosition().y > currentPlayer->myBody->GetPosition().y && (myBody->GetPosition().x - currentPlayer->myBody->GetPosition().x >-0.5f && myBody->GetPosition().x - currentPlayer->myBody->GetPosition().x <0.5f))
	{
		myBody->SetLinearVelocity(b2Vec2(myBody->GetLinearVelocity().x, -100.f));
		ghostMode = sf::seconds(1.f/2.f);
	}


	timeSinceLastShot += dt;

	if (timeSinceLastShot >= shootingCooldown)
	{
		shoot();
		soundPlayer->play(SoundEffect::ENEMY_SHOOT);
		timeSinceLastShot -= shootingCooldown;
	}


	if (currentHP <= 0)
	{
		soundPlayer->play(SoundEffect::ENEMY_DIES);
		globalQueuedForDeletion->push_back(this);
		SceneNode *tmp;
		tmp = new NonPhysical(Textures::ENEMY_FIGHTER, sf::IntRect(0, 25, 30, 25), 0, 0, 0, getPosition().x, getPosition().y + 13, 50, 0);
		globalQueuedForInsertion->push_back(Ptr(tmp));
		tmp = new NonPhysical(Textures::ENEMY_FIGHTER, sf::IntRect(0, 0, 30, 25), ((rand() % 200) / 100.f) - 1.f, ((rand() % 200) / 100.f) - 2.f, (rand() % 20) - 10.f, getPosition().x, getPosition().y - 13, 50);
		globalQueuedForInsertion->push_back(Ptr(tmp));
		//return;
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
	if (anotherNode->MyId == ObjectId::FRIENDLY_BULLET) {
		soundPlayer->play(SoundEffect::ENEMY_HIT);
		damage(anotherNode->getDamage());
	}
}


void EnemyFighter::endContact(SceneNode* anotherNode)
{
	
}

void EnemyFighter::preSolve(b2Contact* contact, SceneNode* anotherNode){
	if (anotherNode->MyId == ObjectId::PLATFORM&&ghostMode>sf::Time::Zero)
		contact->SetEnabled(false);
}