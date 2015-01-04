#include "Map.h"


Map::Map (unsigned int numberOfSpawns, Dimensions size, Dimensions biggestPlatform, Dimensions smallestPlatform, unsigned int numberOfPlatforms) : mSize (size), mBiggestPlatform (biggestPlatform), mSmallestPlatform (smallestPlatform), mNumberOfPlatforms (numberOfPlatforms), mNumberOfSpawns (numberOfSpawns) {
    generate ();
    globalRoot->attachChild (SceneNode::Ptr (this));
}

Map::~Map () {
}


void Map::generate () {
    //walls
    Platform * ceiling = new Platform ({0.f, 0.f}, {mSize.first - 1, 1});
    Platform * rightWall = new Platform ({ceiling->getCorner (2).x, 0.f}, {1, mSize.second - 1});
    Platform * leftWall = new Platform ({0.f, ceiling->getCorner (2).y}, {1, mSize.second - 1});
    Platform * floor = new Platform ({0.f, leftWall->getCorner (3).y}, {mSize.first, 1});

    attachChild (SceneNode::Ptr (ceiling));
    attachChild (SceneNode::Ptr (leftWall));
    attachChild (SceneNode::Ptr (rightWall));
    attachChild (SceneNode::Ptr (floor));

    //platforms
    attachChild (SceneNode::Ptr (new Platform ({70.f, 250.f}, {20, 1})));
    attachChild (SceneNode::Ptr (new Platform ({500.f, 350.f}, {13, 1})));
    attachChild (SceneNode::Ptr (new Platform ({50.f, 500.f}, {13, 1})));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 550.f}, {13, 1})));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 150.f}, {3, 1})));
    attachChild (SceneNode::Ptr (new Platform ({800.f, 70.f}, {1, 5})));

    //spawns
    for (int i = 0; i < mNumberOfSpawns; i++) {
        mSpawnList.push_back ({float (rand () % 600), float (rand () % 1200)});
    }
}