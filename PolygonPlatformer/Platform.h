#pragma once
#include "SceneNode.h"
#include "PlatformAtom.h"


class Platform : public SceneNode {
public:

    struct Corner {        //can be halpful with pathfinding
        sf::Vector2f leftUp, leftDown, rigthUp, rightDown;
    };

    Platform (sf::Vector2f position = {0.f, 0.f}, std::pair<int, int> dimensions = {0, 0});   //vector specifies left upper corner of the platform
    ~Platform ();

    Corner getCorner ();
    sf::Vector2f getCorner (int corner);    //12
                                            //34

private:
    Corner mCorners;

    b2BodyDef platformBodyDef;
    b2PolygonShape platformBox;
};

