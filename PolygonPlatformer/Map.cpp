#include "Map.h"
#include <stdlib.h>
#include <math.h>

Map::Map (unsigned int numberOfSpawns, Dimensions size, unsigned int numberOfPlatforms, Dimensions biggestPlatform, Dimensions smallestPlatform, float minimalDistance) : mSize (size), mBiggestPlatform (biggestPlatform), mSmallestPlatform (smallestPlatform), mNumberOfPlatforms (numberOfPlatforms), mNumberOfSpawns (numberOfSpawns), mMinimalDistance (minimalDistance) {
    generate ();
    globalRoot->attachChild (SceneNode::Ptr (this));
}

Map::~Map () {
}


void Map::generate () {
    //walls
    Platform * ceiling = new Platform ({0.f, 0.f}, {mSize.first - 1, 1}, true);
    Platform * rightWall = new Platform ({ceiling->getCorner (2).x, 0.f}, {1, mSize.second}, true);
    Platform * leftWall = new Platform ({0.f, ceiling->getCorner (3).y}, {1, mSize.second - 1}, true);
    Platform * floor = new Platform ({0.f, leftWall->getCorner (3).y}, {mSize.first, 1}, true);

    attachChild (SceneNode::Ptr (ceiling));
    attachChild (SceneNode::Ptr (leftWall));
    attachChild (SceneNode::Ptr (rightWall));
    attachChild (SceneNode::Ptr (floor));

    mBrickHeight = floor->getBrickHeight ();
    mBrickWidth = floor->getBrickWidth ();
    mHeight = mSize.second * mBrickHeight;
    mWidth = mSize.first * mBrickWidth;

    placePlatforms ();

    while (lookForCollisions (mMinimalDistance));

    handleOuties ();

    //spawns
    for (int i = 0; i < mNumberOfSpawns; i++) {
        mSpawnList.push_back ({float (rand () % 600), float (rand () % 1200)});
    }
}

bool Map::isPointInside (Platform * platform, sf::Vector2f point, float sensitivity) {
    Platform::Corner corners = platform->getCorner ();
    corners.leftUp = corners.leftUp + sf::Vector2f({-sensitivity, -sensitivity});
    corners.rigthUp = corners.rigthUp + sf::Vector2f ({sensitivity, -sensitivity});
    corners.rightDown = corners.rightDown + sf::Vector2f ({sensitivity, sensitivity});
    corners.leftDown = corners.leftDown + sf::Vector2f ({-sensitivity, sensitivity});

    if (corners.leftDown.x < point.x)
        if (corners.rightDown.x > point.x)
            if (corners.leftUp.y < point.y)
                if (corners.leftDown.y > point.y)
                    return true;

    return false;
}

bool Map::isCollision (Platform * platformA, Platform * platformB, float sensitivity) {
    Platform::Corner cornersA = platformA->getCorner ();
    Platform::Corner cornersB = platformB->getCorner ();

    //if any vertex insite other platform
    if (isPointInside (platformB, cornersA.leftUp, sensitivity) || isPointInside (platformB, cornersA.leftDown, sensitivity) || isPointInside (platformB, cornersA.rightDown, sensitivity) || isPointInside (platformB, cornersA.rigthUp, sensitivity) ||
        isPointInside (platformA, cornersB.leftUp, sensitivity) || isPointInside (platformA, cornersB.leftDown, sensitivity) || isPointInside (platformA, cornersB.rightDown, sensitivity) || isPointInside (platformA, cornersB.rigthUp, sensitivity))
        return true;

    //if cross or one platform inside another
    if (((cornersB.leftDown.x >= cornersA.leftDown.x && cornersB.rightDown.x <= cornersA.rightDown.x) ||
        (cornersB.leftDown.x <= cornersA.leftDown.x && cornersB.rightDown.x >= cornersA.rightDown.x))
        &&
        ((cornersB.leftUp.y <= cornersA.leftUp.y && cornersB.leftDown.y >= cornersA.leftDown.y) ||
        (cornersB.leftUp.y >= cornersA.leftUp.y && cornersB.leftDown.y <= cornersA.leftDown.y)))
        return true;

    return false;
}

bool Map::lookForCollisions (float sensitivity) {
    if (!mNumberOfPlatforms) return false;

    for (auto itr = mChildren.begin (); itr != mChildren.end (); ++itr) {
        for (auto jtr = itr; jtr != mChildren.end (); ++jtr) {
            if (jtr == itr) continue;
            if (isCollision (static_cast<Platform*>((*itr).get ()), static_cast<Platform*>((*jtr).get ()), sensitivity)) {
                if (static_cast<Platform*>((*itr).get ())->isWall () && static_cast<Platform*>((*jtr).get ())->isWall ())
                    continue;

                handleCollision (static_cast<Platform*>((*itr).get ()), static_cast<Platform*>((*jtr).get ()));
                return true;
            }
        }
    }

    return false;
}

void Map::handleCollision (Platform * platformA, Platform * platformB) {

    if (platformA == static_cast<Platform*>(mChildren[0].get ()))
        platformB->movePlatformRelative ({0.f, 10.f});
    else if (platformA == static_cast<Platform*>(mChildren[2].get ()))
        platformB->movePlatformRelative ({10.f, 0.f});
    else if (platformA == static_cast<Platform*>(mChildren[1].get ()))
        platformB->movePlatformRelative ({-10.f, 0.f});
    else if (platformA == static_cast<Platform*>(mChildren[3].get ()))
        platformB->movePlatformRelative ({0.f, -10.f});
    else if (platformB == static_cast<Platform*>(mChildren[0].get ()))
        platformA->movePlatformRelative ({0.f, 10.f});
    else if (platformB == static_cast<Platform*>(mChildren[2].get ()))
        platformA->movePlatformRelative ({10.f, 0.f});
    else if (platformB == static_cast<Platform*>(mChildren[1].get ()))
        platformA->movePlatformRelative ({-10.f, 0.f});
    else if (platformB == static_cast<Platform*>(mChildren[3].get ()))
        platformA->movePlatformRelative ({0.f, -10.f});

    else {
        switch (rand () % 4) {
            case 0:
                platformA->movePlatformRelative ({10.f, -10.f});
                break;
            case 1:
                platformA->movePlatformRelative ({-10.f, -10.f});
                break;
            case 2:
                platformA->movePlatformRelative ({10.f, 10.f});
                break;
            case 3:
                platformA->movePlatformRelative ({-10.f, 10.f});
                break;
        }
    }
}

void Map::placePlatforms () {
    if (!mNumberOfPlatforms) return;

    int division = ceil (sqrt (mNumberOfPlatforms));
    float dividedWidth = mWidth / division;
    float dividedHeight = mHeight / division;
    int difference = (division*division) - mNumberOfPlatforms;

    /*for (int i = 0; i < mNumberOfPlatforms; i++) {
        int a = (rand () % (mBiggestPlatform.first - mSmallestPlatform.first)) + mSmallestPlatform.first;
        int b = (rand () % 2) + 1;
        float x = (rand () % int (mWidth - (a + 2) * mBrickWidth)) + mBrickWidth;
        float y = (rand () % int (mHeight - (b + 2) * mBrickHeight)) + mBrickHeight;
        Platform * temporary = new Platform ({x, y}, {a, b});
        attachChild (SceneNode::Ptr (temporary));
    }*/

    for (int i = 0; i < division; i++) {
        for (int j = 0; j < division; j++) {
            int a = (rand () % (mBiggestPlatform.first - mSmallestPlatform.first)) + mSmallestPlatform.first;
            int b = (rand () % 2) + 1;

            float x = i * dividedWidth + (rand () % int (dividedWidth)) + mBrickWidth;
            float y = j * dividedHeight + (rand () % int (dividedHeight)) + mBrickHeight;

            Platform * temporary = new Platform ({x, y}, {a, b});
            attachChild (SceneNode::Ptr (temporary));
        }
    }
}

void Map::handleOuties () {
    for (auto itr = mChildren.begin (); itr != mChildren.end (); ++itr) {
        if (static_cast<Platform*>((*itr).get ())->getCorner (2).x < 0 /*|| static_cast<Platform*>((*itr).get ())->getCorner (3).x > 0*/) {
            Platform * out = static_cast<Platform*>((*itr).get ());
            out->movePlatformRelative ({-1000.f, 0});
            //detachChild (*out);
        }
        else if (static_cast<Platform*>((*itr).get ())->getCorner (3).x > mWidth) {
            Platform * out = static_cast<Platform*>((*itr).get ());
            out->movePlatformRelative ({1000.f, 0});
        }
    }
}