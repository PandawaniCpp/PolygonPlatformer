#include "Creature.h"
#include "PlayerState.h"
#include "SceneNode.h"
#include "TextureHolder.h"
#include <Box2D/Box2D.h>
#include "FriendlyBullet.h"


#pragma once




class Player :public Creature {
public:
    PlayerState *currentState;
    Player ();
    virtual void updateCurrent (sf::Time dt, b2World* world = nullptr);
	void beginContact(SceneNode* anotherNode);
	void endContact(SceneNode* anotherNode);
    bool handleEvent (const sf::Event& event);
	void shoot();
    bool isMovingLeft;
    bool isMovingRight;
    bool isJumping;
    bool isAscending;
    bool isFalling;
    sf::Time timeOnGround;
	int contactCounter;
	bool isFacingRight;
	sf::Time shootingCooldown;
	bool isShooting;
	sf::Time timeSinceLastShot;
	int animationCounter;
};
