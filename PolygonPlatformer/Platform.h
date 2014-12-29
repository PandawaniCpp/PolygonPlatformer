#pragma once
#include "SceneNode.h"
#include "PlatformAtom.h"

/*
First shot, platforms only horizontal
*/

class Platform : public SceneNode {
public:

    struct Corner {        //can be halpful with pathfinding
        float leftUp, leftDown, rigthUp, rightDown;
    };

    Platform (sf::Vector2f = {0.f, 0.f}, std::pair<int, int> = {0, 0});   //vector specifies left upper corner of the platform
    ~Platform ();

    Corner getCorner ();

private:
    Corner mCorners;
};

