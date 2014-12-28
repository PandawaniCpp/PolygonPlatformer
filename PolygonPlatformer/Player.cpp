#include "Player.h"

#define PIXELTOMETER (1.f/10.f)

Player::Player() :currentState(new FlyingState), healthbar_red(new SceneNode), healthbar_green(new SceneNode)  {

	MyId = ObjectId::PLAYER;
	contactCounter = 0;
	isFacingRight = true;
	isShooting = false;
	shootingCooldown = sf::seconds (1.f / 5.f);
	animationCounter = 0;
	maxHP = 100;
	currentHP = 100;


	setTexture(globalTextureHolder->get(Textures::PLAYER_RIGHT_ANIMATION));
	setTextureRect(sf::IntRect(0, 0, 30, 50));
	setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f);
	globalRoot->attachChild(Ptr(this));

	b2FixtureDef boxFixtureDef;
	b2PolygonShape boxShape;
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(100.f*PIXELTOMETER, 100.f*PIXELTOMETER);
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

void Player::beginContact(SceneNode* anotherNode)
{
	if (anotherNode->MyId == ObjectId::PLATFORM)
		contactCounter++;
}

void Player::endContact(SceneNode* anotherNode)
{
	if (anotherNode->MyId == ObjectId::PLATFORM)
		contactCounter--;
}

void Player::shoot(){
	SceneNode::Ptr tmp(new FriendlyBullet((myBody->GetPosition().x / PIXELTOMETER), myBody->GetPosition().y / PIXELTOMETER,isFacingRight));
	globalQueuedForInsertion->push_back(tmp);
}



void Player::updateCurrent (sf::Time dt, b2World* world) {
    setPosition (myBody->GetPosition ().x / PIXELTOMETER, myBody->GetPosition ().y / PIXELTOMETER);
	//healthbar_red->setPosition(getPosition().x, getPosition().y - 30.f);
    /*if (myBody->GetLinearVelocity ().y == 0 && currentState)
        currentState->update (this, dt);*/
    if (currentState->id == PlayerStateType::ON_GROUND&&myBody->GetLinearVelocity ().y != 0) {
        delete currentState;
        currentState = new FlyingState;
    }
    if (currentState->id == PlayerStateType::FLYING && myBody->GetLinearVelocity ().y == 0) {
        delete currentState;
        currentState = new OnGroundState;
    }


	timeSinceLastShot += dt;
	if (!isShooting&&timeSinceLastShot >= shootingCooldown)
		timeSinceLastShot = shootingCooldown;


	if (timeSinceLastShot >= shootingCooldown&&isShooting)
	{
		shoot();
		timeSinceLastShot -= shootingCooldown;
	}



	if (isMovingLeft&&!isMovingRight)
		isFacingRight = false;
	if (isMovingRight&&!isMovingLeft)
		isFacingRight = true;

    if (myBody->GetLinearVelocity ().y != 0)
        timeOnGround = sf::Time::Zero;
    if (myBody->GetLinearVelocity ().y == 0)
        timeOnGround += dt;

    if (timeOnGround.asSeconds() >= 2.f / 60.f) {
        isFalling = true;
        isAscending = false;
    }

    if (!(isMovingLeft || isMovingRight))
        myBody->SetLinearVelocity (b2Vec2 (0.f, myBody->GetLinearVelocity ().y));

    if (!(isMovingLeft&&isMovingRight)) {

        if (isMovingLeft)
            myBody->SetLinearVelocity (b2Vec2 (-30.f, myBody->GetLinearVelocity ().y));
        if (isMovingRight)
            myBody->SetLinearVelocity (b2Vec2 (30.f, myBody->GetLinearVelocity ().y));
    }

    if (myBody->GetLinearVelocity ().y > 0) {

        isFalling = true;
        isAscending = false;
    }
    if (myBody->GetLinearVelocity ().y < 0) {

        isFalling = false;
        isAscending = true;
    }

    if (isJumping&&currentState->id == PlayerStateType::ON_GROUND&&isAscending==false)
        myBody->SetLinearVelocity (b2Vec2 (myBody->GetLinearVelocity ().x, -50.f));

	if (!isMovingLeft&&isMovingRight)
	{
		setTexture(globalTextureHolder->get(Textures::PLAYER_RIGHT_ANIMATION));
		setTextureRect(sf::IntRect(30 * (animationCounter/2), 0, 30, 50));
		animationCounter++;
		animationCounter %= 12;
		//setTexture(globalTextureHolder->get(Textures::PLAYER_RIGHT));
	}
	else if (isMovingLeft&&!isMovingRight)
	{
		//setTexture(globalTextureHolder->get(Textures::PLAYER_LEFT));
		setTextureRect(sf::IntRect(0, 0, 30, 50));
		setTextureRect(sf::IntRect(30 * (animationCounter / 2), 0, 30, 50));
		animationCounter--;
		if (animationCounter < 0)
			animationCounter = 11;

	}
	/*if (contactCounter == 0)
	{
		setTexture(globalTextureHolder->get(Textures::PLAYER_JUMPING));
	}

	if (contactCounter > 0)
	{
		setTexture(globalTextureHolder->get(Textures::PLAYER_RIGHT));
	}*/
	healthbar_red->setPosition(myBody->GetPosition().x / PIXELTOMETER, (myBody->GetPosition().y / PIXELTOMETER) - 30.f);
	healthbar_green->setPosition(myBody->GetPosition().x / PIXELTOMETER, (myBody->GetPosition().y / PIXELTOMETER) - 30.f);
	healthbar_green->setTextureRect(sf::IntRect(0, 0, static_cast<int>(25 * (currentHP / maxHP)), 4));
	if (currentHP < 0)
		currentHP = 0;
}

bool Player::handleEvent (const sf::Event& event) {

    switch (event.type) {
        case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::K)
			{
				isShooting = true;
				/*SceneNode::Ptr tmp(new FriendlyBullet(globalWorld, globalTextureHolder, (myBody->GetPosition().x / PIXELTOMETER), myBody->GetPosition().y / PIXELTOMETER,globalRoot,globalQueuedForDeletion,isFacingRight));
				globalRoot->attachChild(tmp);*/
				//globalRoot->detachChild(*(tmp.get()));
			}
			if (event.key.code == sf::Keyboard::P)
			{
				damage(10);
			}

            currentState->handleEvent (this, event);
            break;

        case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::K)
			{
				isShooting = false;
				
			}
            currentState->handleEvent (this, event);
            break;
    }

    return true;
}