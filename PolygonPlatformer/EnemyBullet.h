#pragma once

#include "SceneNode.h"
#include "TextureHolder.h"


class EnemyBullet : public SceneNode{
public:
	EnemyBullet(float positionX, float positionY, bool facingRight);
	~EnemyBullet();
	void beginContact(SceneNode* anotherNode);
	void preSolve(b2Contact* contact, SceneNode* anotherNode);
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	float velocity;
	float height;
	int current_direction;
};