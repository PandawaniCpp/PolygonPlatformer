#include "NonPhysical.h"


NonPhysical::NonPhysical(Textures::ID texture, sf::IntRect textureRect, float xSpeedArg, float ySpeedArg,float rotationArg, float xPosition, float yPosition, int framesToFadeArg, float gravityArg){
	xSpeed = xSpeedArg;
	ySpeed = ySpeedArg;
	setTexture(globalTextureHolder->get(texture));
	setTextureRect(textureRect);
	setOrigin(getTextureRect().width / 2.f, getTextureRect().height / 2.f);
	setPosition(xPosition, yPosition);
	framesToFade = framesToFadeArg;
	gravity = gravityArg;
	framesLeft = framesToFade;
	rotation = rotationArg;
	


}




void NonPhysical::updateCurrent(sf::Time dt, b2World* world){
	if (framesLeft <= 0)
		globalQueuedForDeletion->push_back(this);

	setRotation(getRotation() + rotation);
	setPosition(getPosition().x + xSpeed, getPosition().y + ySpeed);
	ySpeed += gravity;
	setColor(sf::Color(255, 255, 255, (255 / framesToFade)*framesLeft));
	--framesLeft;

}