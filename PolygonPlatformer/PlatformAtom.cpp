#include "PlatformAtom.h"

PlatformAtom::PlatformAtom (sf::Vector2f position, TextureHolder &texture, b2World &braveNewWorld) : mPosition (position) {
    groundBodyDef.position.Set (position.x * PIXELTOMETER, position.y * PIXELTOMETER);
    texture.load (Textures::GROUND, "./textures/brick.png");
    setTexture (texture.get (Textures::GROUND));
    b2Body * groundBody = braveNewWorld.CreateBody (&groundBodyDef);
    groundBox.SetAsBox ((getTextureRect ().width / 2.f)*PIXELTOMETER, (getTextureRect ().height / 2.f)*PIXELTOMETER);
    groundBody->CreateFixture (&groundBox, 0.0f);

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