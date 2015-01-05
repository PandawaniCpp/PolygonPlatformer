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
    /*attachChild (SceneNode::Ptr (new Platform ({70.f, 250.f}, {20, 1})));
    attachChild (SceneNode::Ptr (new Platform ({500.f, 350.f}, {13, 1})));
    attachChild (SceneNode::Ptr (new Platform ({50.f, 500.f}, {13, 1})));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 550.f}, {13, 1})));
    attachChild (SceneNode::Ptr (new Platform ({600.f, 150.f}, {3, 1})));
    attachChild (SceneNode::Ptr (new Platform ({800.f, 70.f}, {1, 5})));*/

    /*Platform * testPlatform = new Platform ({100.f, 400.f}, {5, 2});
    testPlatform->movePlatform ({600.f, 400.f});
    attachChild (SceneNode::Ptr(testPlatform));

    Platform * testPlatform2 = new Platform ({100.f, 200.f}, {5, 1});
    attachChild (SceneNode::Ptr (testPlatform2));
*/


    //TESTS
    sf::Vector2f pozycja = {400.f, 400.f};
    PlatformAtom *a1 = new PlatformAtom (pozycja);
    SceneNode::Ptr a1ptr = SceneNode::Ptr (a1);
    attachChild (a1ptr);

    pozycja = {430.f, 400.f};
    PlatformAtom *a2 = new PlatformAtom (pozycja);
    attachChild (SceneNode::Ptr (a2));

    pozycja = {460.f, 400.f};
    PlatformAtom *a3 = new PlatformAtom (pozycja);
    attachChild (SceneNode::Ptr (a3));

    pozycja = {490.f, 400.f};
    PlatformAtom *a4 = new PlatformAtom (pozycja);
    attachChild (SceneNode::Ptr (a4));

    pozycja = {520.f, 400.f};
    PlatformAtom *a5 = new PlatformAtom (pozycja);
    attachChild (SceneNode::Ptr (a5));


    sf::Vector2f transformacja = {110.f, 110.f};
    a1ptr->moveBrickRelative (transformacja);
    a2->moveBrickRelative (transformacja);
    a3->moveBrickRelative (transformacja);
    a4->moveBrickRelative (transformacja);
    a5->moveBrickRelative (transformacja);




    //spawns
    for (int i = 0; i < mNumberOfSpawns; i++) {
        mSpawnList.push_back ({float (rand () % 600), float (rand () % 1200)});
    }
}