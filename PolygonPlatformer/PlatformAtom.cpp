#include "PlatformAtom.h"

PlatformAtom::PlatformAtom (sf::Vector2f position) : mPosition (position) {
    groundBodyDef.type = b2_kinematicBody;
    groundBodyDef.position.Set (mPosition.x * PIXELTOMETER, mPosition.y * PIXELTOMETER);
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

PlatformAtom::~PlatformAtom () {
    globalWorld->DestroyBody (myBody);
}

float PlatformAtom::getWidth () {
    return getTextureRect ().width;
}

float PlatformAtom::getHeight () {
    return getTextureRect ().height;
}

void PlatformAtom::moveBrick (sf::Vector2f newPosition) {
    myBody->SetTransform ({newPosition.x*PIXELTOMETER, newPosition.y*PIXELTOMETER}, myBody->GetAngle ());
    mPosition = newPosition; 
}

void PlatformAtom::moveBrickRelative (sf::Vector2f transformation) {
    sf::Vector2f temp = transformation + mPosition;
    mPosition = temp;
    myBody->SetTransform ({temp.x*PIXELTOMETER, temp.y*PIXELTOMETER}, myBody->GetAngle ());
}
