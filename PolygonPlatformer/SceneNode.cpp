#include "SceneNode.h"
#define PIXELTOMETER (1.f/10.f)
#define RADIANTOANGLE (57.2957795)


std::vector<SceneNode *>* SceneNode::globalQueuedForDeletion = nullptr;
std::vector<SceneNode::Ptr>* SceneNode::globalQueuedForInsertion = nullptr;
SceneNode* SceneNode::globalRoot = nullptr;
b2World* SceneNode::globalWorld = nullptr;
TextureHolder* SceneNode::globalTextureHolder = nullptr;
SoundPlayer* SceneNode::soundPlayer = nullptr;

int SceneNode::fighterOnMap = 0;
int SceneNode::fatOnMap = 0;
int SceneNode::kamikazeOnMap = 0;
int SceneNode::swarmOnMap = 0;
int SceneNode::currentWave = 1;
int SceneNode::globalMoney = 0;


SceneNode::SceneNode (b2World* world) : mParent (nullptr),myBody(nullptr) {
	needsToGetDeleted = false;
}

void SceneNode::attachChild (Ptr child) {
    child->mParent = this;
    mChildren.push_back (std::move (child));
}

SceneNode::Ptr SceneNode::detachChild (const SceneNode& node) {
    auto found = std::find_if (mChildren.begin (), mChildren.end (),
                               [&] (Ptr& p) -> bool { return p.get () == &node; });
   // assert (found != mChildren.end ());//To do: wyrzucaæ b³êdy do loggera
	//if (found != mChildren.end()){


		Ptr result = std::move(*found);
		result->mParent = nullptr;
		mChildren.erase(found);
		return result;
	//}
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