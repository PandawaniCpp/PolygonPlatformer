#pragma once
#include "SceneNode.h"
#include "TextureHolder.h"

#define PIXELTOMETER (1.f/10.f)


class PlatformAtom : public SceneNode {
public:
    PlatformAtom (sf::Vector2f, TextureHolder &, b2World &);
    float getWidth ();      //of texture
    float getHeight ();
    void setPosition (sf::Vector2f);    //position in pxiels not meters of course

private:
    sf::Vector2f mPosition;     //centre of brick
    b2BodyDef groundBodyDef;
    b2PolygonShape groundBox;
};

