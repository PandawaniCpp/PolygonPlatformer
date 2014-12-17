#include "Platform.h"

Platform::Platform (sf::Vector2f position, std::pair<int, int> dimensions, TextureHolder & texture, b2World & world) {
    int brickWidth, brickHeight;
    for (int i = 0; i < dimensions.first; i++) {
        PlatformAtom * temporary = new PlatformAtom ({0.f, 0.f}, texture, world);
        brickWidth = temporary->getWidth ();
        brickHeight = temporary->getHeight ();
        temporary->setPosition ({position.x + brickWidth / 2.f + i*brickWidth, position.y + brickHeight / 2.f});
        attachChild (SceneNode::Ptr (temporary));
    }
}


Platform::~Platform () {
}
