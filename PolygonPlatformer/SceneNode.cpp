#include "SceneNode.h"

SceneNode::SceneNode() : mParent(nullptr){

}

void SceneNode::attachChild(Ptr child){
	mParent = this;
	mChildren.push_back(std::move(child));
}

