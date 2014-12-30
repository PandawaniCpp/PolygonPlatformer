#pragma once
#include "SceneNode.h"


class NonPhysical :public SceneNode{
public:
	NonPhysical(Textures::ID texture,sf::IntRect textureRect,  float xSpeedArg, float ySpeedArg,float rotationArg, float xPosition, float yPosition,int framesToFadeArg, float gravityArg=0.05f);
	virtual void updateCurrent(sf::Time dt, b2World* world = nullptr);
	float xSpeed;
	float ySpeed;
	float gravity;
	int framesToFade;
	int framesLeft;
	float rotation;

};