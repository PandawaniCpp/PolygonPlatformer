#include "Map.h"


Map::Map (std::pair<int, int> size,               //no idea how to use Dimensions typedef in constructor lol
          std::pair<int, int> biggestPlatform,
          std::pair<int, int> smallestPlatform,
          unsigned int numberOfPlatforms,                   //if the biggest size id equal to the smallest, number of platforms can be equal to 1
          TextureHolder & textures, b2World & world) :
          mSize (size),
          mBiggestPlatform (biggestPlatform),
          mSmallestPlatform (smallestPlatform),
          mNumberOfPlatforms (numberOfPlatforms) {
    generate (mSize, mBiggestPlatform, mSmallestPlatform, mNumberOfPlatforms, textures, world);


    mWallBodyDef.position.Set ((1120.0f / 2.f)*PIXELTOMETER, 630.f*PIXELTOMETER);
    b2Body* groundBodyDown = world.CreateBody (&mWallBodyDef);
    mWallLine.SetAsBox ((1120.0f / 2.f)*PIXELTOMETER, 0);
    groundBodyDown->CreateFixture (&mWallLine, 0.0f);

    mWallBodyDef.position.Set ((1120.0f / 2.f)*PIXELTOMETER, 0.f*PIXELTOMETER);
    b2Body* groundBodyUp = world.CreateBody (&mWallBodyDef);
    mWallLine.SetAsBox ((1120.0f / 2.f)*PIXELTOMETER, 0);
    groundBodyUp->CreateFixture (&mWallLine, 0.0f);

    mWallBodyDef.position.Set ((0.f / 2.f)*PIXELTOMETER, (630.f / 2.f)*PIXELTOMETER);
    b2Body* groundBodyLeft = world.CreateBody (&mWallBodyDef);
    mWallLine.SetAsBox (0, (630.0f / 2.f)*PIXELTOMETER);
    groundBodyLeft->CreateFixture (&mWallLine, 0.0f);

    mWallBodyDef.position.Set ((1120.0f)*PIXELTOMETER, (630.f / 2.f)*PIXELTOMETER);
    b2Body* groundBodyRight = world.CreateBody (&mWallBodyDef);
    mWallLine.SetAsBox (0, (630.0f / 2.f)*PIXELTOMETER);
    groundBodyRight->CreateFixture (&mWallLine, 0.0f);
}

Map::~Map () {}


void Map::generate (std::pair<int, int> size, std::pair<int, int> biggestPlatform, std::pair<int, int> smallestPlatform, unsigned int numberOfPlatforms, TextureHolder & textures, b2World & world) {
    attachChild (SceneNode::Ptr (new Platform ({10.f, 250.f}, {20, 1}, textures, world)));
    attachChild (SceneNode::Ptr (new Platform ({500.f, 350.f}, {13, 2}, textures, world)));
    attachChild (SceneNode::Ptr (new Platform ({50.f, 500.f}, {13, 2}, textures, world)));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 550.f}, {13, 2}, textures, world)));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 150.f}, {3, 2}, textures, world)));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 70.f}, {1, 2}, textures, world)));
}