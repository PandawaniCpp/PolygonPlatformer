#pragma once

#include <vector>
#include "SceneNode.h"
#include "Platform.h"
/**
@author: nietup
Brief decritption of the whole level anatomy:
class Map is a collection of platforms, it can add and remove platforms, generate new level etc.
class Platform represents single platform, with its dimensions and position, has collider and is build of sth like...
class PlatformAtom, which is squared texture, has no collider, simple brick used in platforms

Why fuck with atoms? They will be useful in generating platforms different in shape than rectangles - like U-shaped etc.
*/

#define MINIMAL_PLATFORM_RATIO 3    //minimal width to heigth ratio so platforms wont be to squared

class Map : public SceneNode {
public:
    typedef std::pair<int, int> Dimensions;     //1. int specifies the width, 2. - heigth. In PlatformAtoms
    typedef std::vector<sf::Vector2f> PositionsVector;

    Map (unsigned int numberOfSpawns, Dimensions size, unsigned int numberOfPlatforms, Dimensions biggestPlatform, Dimensions smallestPlatform, float minimalDistance);
    ~Map ();

    void generate ();
    bool isPointInside (Platform * platform, sf::Vector2f point, float sensitivity);
    bool isCollision (Platform * platformA, Platform * platformB, float sensitivity);
    bool lookForCollisions (float sensitivity);
    void placePlatforms ();
    void handleCollision (Platform * platformA, Platform * platformB);
    void handleOuties ();

    PositionsVector * getSpawnList () { return &mSpawnList; };
    unsigned int getNumberOfSpawns () { return mSpawnList.size (); };

private:
    PositionsVector mSpawnList;
    Dimensions mSize;
    Dimensions mBiggestPlatform;
    Dimensions mSmallestPlatform;
    unsigned int mNumberOfPlatforms;
    unsigned int mNumberOfSpawns;
    float mBrickWidth;
    float mBrickHeight;
    float mWidth;
    float mHeight;
    float mMinimalDistance;


    b2BodyDef mWallBodyDef;      //kk i dont know how this works yet
    b2PolygonShape mWallLine;
};

