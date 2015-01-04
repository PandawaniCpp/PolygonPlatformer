#include "PlatformAtom.h"

PlatformAtom::PlatformAtom (sf::Vector2f position) : mPosition (position) {
    groundBodyDef.type = b2_kinematicBody;
    groundBodyDef.position.Set (position.x * PIXELTOMETER, position.y * PIXELTOMETER);
    setTexture (globalTextureHolder->get (Textures::GROUND));
    b2Body * groundBody = globalWorld->CreateBody (&groundBodyDef);
    groundBox.SetAsBox ((getTextureRect ().width / 2.f)*PIXELTOMETER, (getTextureRect ().height / 2.f)*PIXELTOMETER);
    groundBody->CreateFixture (&groundBox, 0.0f);

	// Krecik - added it.
	MyId = ObjectId::PLATFORM;
	groundBody->SetUserData(this);
	//end of changes


    myBody = groundBody;
    setOrigin (getTextureRect ().width / 2.f, getTextureRect ().height / 2.f);
}

float PlatformAtom::getWidth () {
    return getTextureRect ().width;
}

float PlatformAtom::getHeight () {
    return getTextureRect ().height;
}

void PlatformAtom::setPosition (sf::Vector2f newPosition) {
    myBody->SetTransform ({newPosition.x*PIXELTOMETER, newPosition.y*PIXELTOMETER}, myBody->GetAngle ());
}