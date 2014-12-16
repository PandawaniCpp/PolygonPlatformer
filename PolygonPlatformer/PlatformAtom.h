#pragma once
#include "SceneNode.h"
#include "TextureHolder.h"

class PlatformAtom : public SceneNode {
public:
    PlatformAtom (sf::Vector2f, TextureHolder &, b2World &);
    float getWidth ();      //of texture
    float getHeight ();
    void setPosition (sf::Vector2f);

private:
    sf::Vector2f mPosition;     //centre of brick
    b2BodyDef groundBodyDef;
    b2PolygonShape groundBox;
};

