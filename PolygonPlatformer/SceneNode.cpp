#include "SceneNode.h"
#define PIXELTOMETER (1.f/10.f)
#define RADIANTOANGLE (57.2957795)

SceneNode::SceneNode (b2World* world) : mParent (nullptr),myBody(nullptr) {

}

void SceneNode::attachChild (Ptr child) {
    child->mParent = this;
    mChildren.push_back (std::move (child));
}

SceneNode::Ptr SceneNode::detachChild (const SceneNode& node) {
    auto found = std::find_if (mChildren.begin (), mChildren.end (),
                               [&] (Ptr& p) -> bool { return p.get () == &node; });
    assert (found != mChildren.end ());//To do: wyrzuca� b��dy do loggera
    Ptr result = std::move (*found);
    result->mParent = nullptr;
    mChildren.erase (found);
    return result;
}

void SceneNode::update (sf::Time dt, b2World* world) {
    this->updateCurrent (dt);
    for (auto itr = mChildren.begin ();
         itr != mChildren.end (); ++itr) {
        (*itr)->update (dt);
    }
}

void SceneNode::updateCurrent (sf::Time dt, b2World* world) {
    if (myBody != nullptr) {

        setPosition (myBody->GetPosition ().x / PIXELTOMETER, myBody->GetPosition ().y / PIXELTOMETER);
        setRotation (myBody->GetAngle ()*RADIANTOANGLE);
    }
}


void SceneNode::draw (sf::RenderTarget& target) const {

    this->drawCurrent (target);
    for (auto itr = mChildren.begin ();
         itr != mChildren.end (); ++itr) {
        (*itr)->draw (target);
    }
}

void SceneNode::drawCurrent (sf::RenderTarget& target) const {
    target.draw (*this);
}