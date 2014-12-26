#include "Player.h"

#define PIXELTOMETER (1.f/10.f)

Player::Player () :currentState (new FlyingState)  {
	 //myTextureHolder.load(Textures::PLAYER_JUMPING, "./textures/player_jumping.png");
	MyId = ObjectId::PLAYER;
	contactCounter = 0;
	isFacingRight = true;
	isShooting = false;
	shootingCooldown = sf::seconds (1.f / 5.f);
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
	SceneNode::Ptr tmp(new FriendlyBullet(globalWorld, globalTextureHolder, (myBody->GetPosition().x / PIXELTOMETER), myBody->GetPosition().y / PIXELTOMETER, globalRoot, globalQueuedForDeletion, isFacingRight));
	//globalRoot->attachChild(tmp);
	globalQueuedForInsertion->push_back(tmp);
}



void Player::updateCurrent (sf::Time dt, b2World* world) {
    setPosition (myBody->GetPosition ().x / PIXELTOMETER, myBody->GetPosition ().y / PIXELTOMETER);
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

	if (isFacingRight)
		setTexture(globalTextureHolder->get(Textures::PLAYER_RIGHT));
	else
		setTexture(globalTextureHolder->get(Textures::PLAYER_LEFT));
	/*if (contactCounter == 0)
	{
		setTexture(globalTextureHolder->get(Textures::PLAYER_JUMPING));
	}

	if (contactCounter > 0)
	{
		setTexture(globalTextureHolder->get(Textures::PLAYER_RIGHT));
	}*/

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