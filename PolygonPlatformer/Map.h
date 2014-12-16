#pragma once
#include "SceneNode.h"
/**
@author: nietup
Brief decritption of the whole level anatomy:
class Map is a collection of platforms, it can add and remove platforms, generate new level etc.
class Platform represents single platform, with its dimensions and position, has collider and is build of sth like...
class PlatformAtom, which is squared texture, has no collider, simple brick used in platforms

Why fuck with atoms? They will be useful in generating platforms different in shape than rectangles - like U-shaped etc.
*/

class Map : public SceneNode {
public:
    Map (std::pair<int, int>, std::pair<int, int>, std::pair<int, int>, unsigned int);
    ~Map ();
    void generate (std::pair<int, int>, std::pair<int, int>, std::pair<int, int>, unsigned int);

    typedef std::pair<int, int> Dimensions;     //1. int specifies the width, 2. - heigth. In PlatformAtoms

private:
    Dimensions mSize;
    Dimensions mBiggestPlatform;
    Dimensions mSmallestPlatform;
    unsigned int mNumberOfPlatforms;
};

