#include "EnemyFat.h"
#include "Player.h"
#include "Pickup.h"

#define PIXELTOMETER (1.f/10.f)




EnemyFat::~EnemyFat(){
	globalWorld->DestroyBody(myBody);
	--fatOnMap;
	Player::me->heal(Player::me->hpPerMob*4);


    globalMoney += 16 + (4 * currentWave);

    if (rand () % 20 == 0)
        new Pickup (getPosition ().x, getPosition ().y, ObjectId::PICKUP_FRENZY);
    if (rand () % 5 == 0)
        new Pickup (getPosition ().x, getPosition ().y, ObjectId::PICKUP_BLOODLUST);

}






EnemyFat::EnemyFat(float x, float y) :healthbar_red(new SceneNode), healthbar_green(new SceneNode){

    ghostMode = sf::Time::Zero;

	++fatOnMap;


	MyId = ObjectId::ENEMY_FAT;

	maxHP = 150+(20*(currentWave-1));


	currentHP = maxHP;
	jumpingCooldown = sf::seconds(1.5);
	timeSinceLastJump = sf::Time::Zero;
	//ghostMode = sf::Time::Zero;


	setTexture(globalTextureHolder->get(Textures::ENEMY_FAT));
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
	boxFixtureDef.friction = 0.5;
	dynamicBody->CreateFixture(&boxFixtureDef);
	dynamicBody->SetFixedRotation(true);
	dynamicBody->SetUserData(this);
	myBody = dynamicBody;



	/*textures->load(Textures::HEALTHBAR_RED, "./textures/healthbar_red.png");
	textures->load(Textures::HEALTHBAR_GREEN, "./textures/healthbar_green.png");*/
	healthbar_red->setTexture(globalTextureHolder->get(Textures::HEALTHBAR_RED));
	healthbar_green->setTexture(globalTextureHolder->get(Textures::HEALTHBAR_GREEN));
	healthbar_red->setPosition(getPosition().x, getPosition().y - 55.f);
	healthbar_green->setPosition(getPosition().x, getPosition().y - 55.f);
	attachChild(healthbar_red);
	attachChild(healthbar_green);
	healthbar_green->setOrigin(healthbar_green->getTextureRect().width / 2.f, healthbar_green->getTextureRect().height / 2.f);
	healthbar_red->setOrigin(healthbar_red->getTextureRect().width / 2.f, healthbar_red->getTextureRect().height / 2.f);


}

void EnemyFat::jump()
{
	if (currentPlayer->getPosition().x < getPosition().x)
		myBody->SetLinearVelocity(b2Vec2(-20.f, -20.f));
	else
		myBody->SetLinearVelocity(b2Vec2(20.f, -20.f));

    ghostMode = sf::seconds (1.f / 3.f);
	
}


void EnemyFat::updateCurrent(sf::Time dt, b2World* world){

	
    ghostMode -= dt;
    if (ghostMode <= sf::Time::Zero)
        ghostMode = sf::Time::Zero;


    if (getPosition ().y >= 6000)
        damage (maxHP);



	timeSinceLastJump += dt;

	if (timeSinceLastJump >= jumpingCooldown)
	{
		jump();
		soundPlayer->play(SoundEffect::ENEMY_SHOOT);
		timeSinceLastJump -= jumpingCooldown;
	}


	if (currentHP <= 0)
	{
		soundPlayer->play(SoundEffect::ENEMY_DIES);
		globalQueuedForDeletion->push_back(this);
		SceneNode *tmp;

		for (int i = 0; i < 5; i++)
		{

			for (int j = 0; j < 5; j++)
			{
				tmp = new NonPhysical(Textures::ENEMY_FAT, sf::IntRect(j * 20, i * 20, 20, 20), ((rand() % 200) / 100.f) - 1.f, ((rand() % 200) / 100.f) - 1.f, rand() % 5, getPosition().x + (20 * (j - 2)), getPosition().y + (20 * (i - 2)), 50);
				globalQueuedForInsertion->push_back(Ptr(tmp));

				int size;
				for (int k = (rand() % 7) - 3; k < 9; ++k)
				{
					size = rand() % 5;
					tmp = new NonPhysical(Textures::BLOOD, sf::IntRect(0, 0, size, size), ((rand() % 400) / 100.f) - 2.f, ((rand() % 400) / 100.f) - 2.f, 20, getPosition().x + (20 * (j - 2)), getPosition().y + (20 * (i - 2)), 50);
					globalQueuedForInsertion->push_back(Ptr(tmp));
				}

			}

		}




		/*tmp = new NonPhysical(Textures::ENEMY_FIGHTER, sf::IntRect(0, 25, 30, 25), 0, 0, 0, getPosition().x, getPosition().y + 13, 50, 0);
		globalQueuedForInsertion->push_back(Ptr(tmp));
		tmp = new NonPhysical(Textures::ENEMY_FIGHTER, sf::IntRect(0, 0, 30, 25), ((rand() % 200) / 100.f) - 1.f, ((rand() % 200) / 100.f) - 2.f, (rand() % 20) - 10.f, getPosition().x, getPosition().y - 13, 50);
		globalQueuedForInsertion->push_back(Ptr(tmp));*/
		//return;
	}

	setPosition(myBody->GetPosition().x / PIXELTOMETER, myBody->GetPosition().y / PIXELTOMETER);



	healthbar_red->setPosition(myBody->GetPosition().x / PIXELTOMETER, (myBody->GetPosition().y / PIXELTOMETER) - 55.f);
	healthbar_green->setPosition(myBody->GetPosition().x / PIXELTOMETER, (myBody->GetPosition().y / PIXELTOMETER) - 55.f);
	healthbar_green->setTextureRect(sf::IntRect(0, 0, static_cast<int>(25 * (currentHP / maxHP)), 4));
	if (currentHP < 0)
		currentHP = 0;



}



void EnemyFat::beginContact(SceneNode* anotherNode)
{
	if (anotherNode->MyId == ObjectId::FRIENDLY_BULLET) {
		soundPlayer->play(SoundEffect::ENEMY_HIT);
		damage(anotherNode->getDamage());
	}
}


void EnemyFat::endContact(SceneNode* anotherNode)
{

}

/*void EnemyFighter::preSolve(b2Contact* contact, SceneNode* anotherNode){
	if (anotherNode->MyId == ObjectId::PLATFORM&&ghostMode>sf::Time::Zero)
		contact->SetEnabled(false);
}*/


void EnemyFat::preSolve (b2Contact* contact, SceneNode* anotherNode) {
    if (anotherNode->MyId == ObjectId::PLATFORM&&ghostMode>sf::Time::Zero)
        contact->SetEnabled (false);
}
