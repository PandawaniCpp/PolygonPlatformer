#include "Platform.h"

Platform::Platform (sf::Vector2f position, std::pair<int, int> dimensions, TextureHolder & texture, b2World & world) {
    int brickWidth, brickHeight;
    PlatformAtom * looser = new PlatformAtom ({0.f, 0.f}, texture, world);
    brickWidth = brickHeight = looser->getWidth();     //ya dats lame ill change it when i figure out how to change atoms position
    for (int i = 0; i < dimensions.first; i++) {
        PlatformAtom * temporary = new PlatformAtom ({position.x + brickWidth / 2.f + i*brickWidth, position.y + brickHeight / 2.f}, texture, world);
        /*brickWidth = temporary->getWidth ();
        brickHeight = temporary->getHeight ();
        temporary->setPosition ({position.x + brickWidth / 2.f + i*brickWidth, brickHeight / 2.f});*/
        attachChild (SceneNode::Ptr (temporary));
    }
}


Platform::~Platform () {
}
