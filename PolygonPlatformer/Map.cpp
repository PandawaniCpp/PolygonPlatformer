#include "Map.h"


Map::Map (unsigned int numberOfEnemies, Dimensions size, Dimensions biggestPlatform, Dimensions smallestPlatform, unsigned int numberOfPlatforms) : mSize (size), mBiggestPlatform (biggestPlatform), mSmallestPlatform (smallestPlatform), mNumberOfPlatforms (numberOfPlatforms), mNumberOfEnemies (numberOfEnemies) {
    generate ();
    globalRoot->attachChild (SceneNode::Ptr (this));
}

Map::~Map () {}


void Map::generate () {
    attachChild (SceneNode::Ptr (new Platform ({10.f, 250.f}, {20, 1})));
    attachChild (SceneNode::Ptr (new Platform ({500.f, 350.f}, {13, 2})));
    attachChild (SceneNode::Ptr (new Platform ({50.f, 500.f}, {13, 2})));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 550.f}, {13, 2})));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 150.f}, {3, 2})));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 70.f}, {1, 2})));

    mWallBodyDef.position.Set ((1120.0f / 2.f)*PIXELTOMETER, 630.f*PIXELTOMETER);
    b2Body* groundBodyDown = globalWorld->CreateBody (&mWallBodyDef);
    mWallLine.SetAsBox ((1120.0f / 2.f)*PIXELTOMETER, 0);
    groundBodyDown->CreateFixture (&mWallLine, 0.0f);

    mWallBodyDef.position.Set ((1120.0f / 2.f)*PIXELTOMETER, 0.f*PIXELTOMETER);
    b2Body* groundBodyUp = globalWorld->CreateBody (&mWallBodyDef);
    mWallLine.SetAsBox ((1120.0f / 2.f)*PIXELTOMETER, 0);
    groundBodyUp->CreateFixture (&mWallLine, 0.0f);

    mWallBodyDef.position.Set ((0.f / 2.f)*PIXELTOMETER, (630.f / 2.f)*PIXELTOMETER);
    b2Body* groundBodyLeft = globalWorld->CreateBody (&mWallBodyDef);
    mWallLine.SetAsBox (0, (630.0f / 2.f)*PIXELTOMETER);
    groundBodyLeft->CreateFixture (&mWallLine, 0.0f);

    mWallBodyDef.position.Set ((1120.0f)*PIXELTOMETER, (630.f / 2.f)*PIXELTOMETER);
    b2Body* groundBodyRight = globalWorld->CreateBody (&mWallBodyDef);
    mWallLine.SetAsBox (0, (630.0f / 2.f)*PIXELTOMETER);
    groundBodyRight->CreateFixture (&mWallLine, 0.0f);

    for (int i = 0; i < mNumberOfEnemies; i++) {
        mSpawnList.push_back ({float(rand () % 600), float(rand () % 1200)});
    }
}