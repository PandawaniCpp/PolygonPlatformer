#include "Platform.h"

Platform::Platform (sf::Vector2f position, std::pair<int, int> dimensions) {
    float brickWidth, brickHeight;
    for (int i = 0; i < dimensions.first; i++) {
        PlatformAtom * temporary = new PlatformAtom ();
        brickWidth = temporary->getWidth ();
        brickHeight = temporary->getHeight ();
        temporary->setPosition ({position.x + brickWidth / 2.f + i*brickWidth, position.y + brickHeight / 2.f});
        attachChild (SceneNode::Ptr (temporary));
    }
}


Platform::~Platform () {
}
