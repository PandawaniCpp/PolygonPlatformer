#include "SceneNode.h"

SceneNode::SceneNode() : mParent(nullptr){

}

void SceneNode::attachChild(Ptr child){
	mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](Ptr& p) -> bool { return p.get() == &node; });
	assert(found != mChildren.end());//To do: wyrzucaæ b³êdy do loggera
	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target,
	sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	for (auto itr = mChildren.begin();
		itr != mChildren.end(); ++itr)
	{
		(*itr)->draw(target, states);
	}
}
