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
	static Player* me;
    virtual void updateCurrent (sf::Time dt, b2World* world = nullptr);
	void beginContact(SceneNode* anotherNode);
	void endContact(SceneNode* anotherNode);
    bool handleEvent (const sf::Event& event);
	void shoot();
	void damage(unsigned amount);
    bool isMovingLeft;
    bool isMovingRight;
    bool isJumping;
    bool isAscending;
    bool isFalling;
    sf::Time timeOnGround;
	int contactCounter;
	bool isFacingRight;
	sf::Time shootingCooldown;
	sf::Time touchingDamageCooldown;
	sf::Time timeSinceLastDamage;
	bool isShooting;
	sf::Time timeSinceLastShot;
	int animationCounter;
	Ptr healthbar_red;
	Ptr healthbar_green;

	float bulletDamageVar;
	float hpPerMob;
	bool piercingBullets;


};
