#pragma once
#include "SceneNode.h"
#include "PlatformAtom.h"


class Platform : public SceneNode {
public:

    struct Corner {        //can be halpful with pathfinding
        sf::Vector2f leftUp, leftDown, rigthUp, rightDown;
    };

    Platform (sf::Vector2f position = {0.f, 0.f}, std::pair<int, int> dimensions = {0, 0}, bool wall = 0);   //vector specifies left upper corner of the platform
    ~Platform ();

    void updateCorners (sf::Vector2f leftUp);
    void movePlatform (sf::Vector2f leftUpperCorner);
    void movePlatformRelative (sf::Vector2f leftUpperCorner);

    float getBrickWidth () { return brickWidth; };
    float getBrickHeight () { return brickHeight; };
    Corner getCorner ();
    sf::Vector2f getCorner (int corner);    //12
                                            //34

    bool isWall () { return mWall; };
    void setAsWall ();

private:
    Corner mCorners;
    float brickWidth, brickHeight;
    std::pair<int, int> mDimensions;
    sf::Vector2f mWidth;
    sf::Vector2f mHeight;
    bool mWall;

    //b2BodyDef platformBodyDef;
    //b2PolygonShape platformBox;
};

