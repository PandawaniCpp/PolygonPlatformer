#include "Platform.h"

Platform::Platform (sf::Vector2f position, std::pair<int, int> dimensions) {
    float brickWidth, brickHeight;
    mCorners.leftUp = position;
    for (int i = 0; i < dimensions.first; i++) {
        PlatformAtom * temporaryX = new PlatformAtom ();
        brickWidth = temporaryX->getWidth ();
        brickHeight = temporaryX->getHeight ();
        temporaryX->setPosition ({position.x + brickWidth / 2.f + i*brickWidth, position.y + brickHeight / 2.f});
        attachChild (SceneNode::Ptr (temporaryX));

        for (int j = 0; j < dimensions.second; j++) {
            PlatformAtom * temporaryY = new PlatformAtom ();
            temporaryY->setPosition ({position.x + brickWidth / 2.f + i*brickWidth, position.y + brickHeight / 2.f + j*brickHeight});
            attachChild (SceneNode::Ptr (temporaryY));
        }
    }
    mCorners.leftDown = mCorners.rigthUp = mCorners.leftUp;
    mCorners.leftDown.y += brickHeight * dimensions.second;
    mCorners.rigthUp.x += brickWidth * dimensions.first;
    mCorners.rightDown = mCorners.rigthUp;
    mCorners.rightDown.y += brickHeight * dimensions.second;

    //box2d stuff
    b2Vec2 vertices[4];
    vertices[0].Set (mCorners.leftUp.x * PIXELTOMETER, mCorners.leftUp.y * PIXELTOMETER);
    vertices[1].Set (mCorners.rigthUp.x * PIXELTOMETER, mCorners.rigthUp.y * PIXELTOMETER);
    vertices[2].Set (mCorners.rightDown.x * PIXELTOMETER, mCorners.rightDown.y * PIXELTOMETER);
    vertices[3].Set (mCorners.leftDown.x * PIXELTOMETER, mCorners.leftDown.y * PIXELTOMETER);

    platformBox.Set (vertices, 4); //pass array to the shape
//    platformBodyDef.position.Set ();

    //myFixtureDef.shape = &polygonShape; //change the shape of the fixture
    //myBodyDef.position.Set (0, 20); //in the middle
    //b2Body* dynamicBody2 = m_world->CreateBody (&myBodyDef);
    //dynamicBody2->CreateFixture (&myFixtureDef); //add a fixture to the body
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