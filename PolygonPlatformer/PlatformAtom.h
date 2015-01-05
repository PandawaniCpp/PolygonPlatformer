#pragma once
#include "SceneNode.h"
#include "TextureHolder.h"

#define PIXELTOMETER (1.f/10.f)


class PlatformAtom : public SceneNode {
public:
    PlatformAtom (sf::Vector2f position = {0.f, 0.f});
    ~PlatformAtom ();
    float getWidth ();      //of texture
    float getHeight ();
    void moveBrick (sf::Vector2f);
    void moveBrickRelative (sf::Vector2f);

    sf::Vector2f getBrickCenter () { return mPosition; }

private:
    sf::Vector2f mPosition;     //centre of brick
    b2BodyDef groundBodyDef;
    b2PolygonShape groundBox;
};

