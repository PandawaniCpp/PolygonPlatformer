/* Only a concept of a class.*/

#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
class SceneNode : sf::Sprite{

public:
	typedef std::unique_ptr<SceneNode> Ptr;

	SceneNode();

	void attachChild(Ptr child);

protected:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};