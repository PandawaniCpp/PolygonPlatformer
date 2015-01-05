#include "Platform.h"

Platform::Platform (sf::Vector2f position, std::pair<int, int> dimensions) : mDimensions(dimensions) {
    mCorners.leftUp = position;

    for (int i = 0; i < dimensions.first; i++) {
        for (int j = 0; j < dimensions.second; j++) {
            PlatformAtom * temporary = new PlatformAtom ();
            brickWidth = temporary->getWidth ();
            brickHeight = temporary->getHeight ();
            temporary->moveBrick ({position.x + brickWidth / 2.f + i*brickWidth, position.y + brickHeight / 2.f + j*brickHeight});
            attachChild (SceneNode::Ptr (temporary));
        }
    }

    mCorners.leftDown = mCorners.rigthUp = mCorners.leftUp;
    mCorners.leftDown.y += brickHeight * dimensions.second;
    mCorners.rigthUp.x += brickWidth * dimensions.first;
    mCorners.rightDown = mCorners.rigthUp;
    mCorners.rightDown.y += brickHeight * dimensions.second;

    //box2d stuff
//    platformBodyDef.type = b2_kinematicBody;
//    platformBodyDef.position.Set (((mCorners.leftDown.x + mCorners.rightDown.x) / 2.f) * PIXELTOMETER, ((mCorners.leftUp.y + mCorners.leftDown.y) / 2.f) * PIXELTOMETER);
//
//    b2Body * platformBody = globalWorld->CreateBody (&platformBodyDef);
//
//    b2Vec2 vertices[4];
//    vertices[0].Set (mCorners.leftUp.x * PIXELTOMETER, mCorners.leftUp.y * PIXELTOMETER);
//    vertices[1].Set (mCorners.rigthUp.x * PIXELTOMETER, mCorners.rigthUp.y * PIXELTOMETER);
//    vertices[2].Set (mCorners.rightDown.x * PIXELTOMETER, mCorners.rightDown.y * PIXELTOMETER);
//    vertices[3].Set (mCorners.leftDown.x * PIXELTOMETER, mCorners.leftDown.y * PIXELTOMETER);
//
//    platformBox.Set (vertices, 4); //pass array to the shape
//    platformBody->CreateFixture (&platformBox, 0.f);
//
//
////    platformBodyDef.position.Set ();
//
//    //myFixtureDef.shape = &polygonShape; //change the shape of the fixture
//    //myBodyDef.position.Set (0, 20); //in the middle
//    //b2Body* dynamicBody2 = m_world->CreateBody (&myBodyDef);
//    //dynamicBody2->CreateFixture (&myFixtureDef); //add a fixture to the body
//
//    myBody = platformBody;
//    setOrigin (((mCorners.leftDown.x + mCorners.rightDown.x) / 2.f) * PIXELTOMETER, ((mCorners.leftUp.y + mCorners.leftDown.y) / 2.f) * PIXELTOMETER);
}


Platform::~Platform () {
}

Platform::Corner Platform::getCorner () {
    Corner temporary = mCorners;
    return temporary;
}

sf::Vector2f Platform::getCorner (int corner) {
    switch (corner) {
        case 1:
            return mCorners.leftUp;
        case 2:
            return mCorners.rigthUp;
        case 3:
            return mCorners.leftDown;
        case 4:
            return mCorners.rightDown;
    }
}

void Platform::movePlatform (sf::Vector2f position) {

    //0 0 vector for testing purpose, it shouldn't change PlatformAtoms position then
    sf::Vector2f transformation = {0.f, 0.f};// {position.x - mCorners.leftUp.x, position.y - mCorners.leftUp.y};

    for (auto itr = mChildren.begin (); itr != mChildren.end (); ++itr) {
        (*itr).get ()->moveBrickRelative (transformation);
    }
}