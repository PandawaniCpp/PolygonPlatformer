#pragma once
#include <memory>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "TextureHolder.h"


namespace ObjectId
{
	enum ID{
		PLAYER, PLATFORM, ENEMY
	};
}





class SceneNode : public sf::Sprite {

public:
    typedef std::shared_ptr<SceneNode> Ptr;

    SceneNode (b2World* world = nullptr);

    void attachChild (Ptr child);
    SceneNode::Ptr detachChild (const SceneNode& node);


    virtual void update (sf::Time dt, b2World* world = nullptr);
    virtual void updateCurrent (sf::Time dt, b2World* world = nullptr);
    virtual void draw (sf::RenderTarget& target)const;
    virtual void drawCurrent (sf::RenderTarget& target) const;
    virtual bool handleEvent (const sf::Event& event) {
        return true;
    };
	virtual void beginContact(SceneNode* anotherNode){};
	virtual void endContact(SceneNode* anotherNode){};

	TextureHolder *globalTextureHolder;
    b2Body* myBody;
	ObjectId::ID MyId;
	
protected:
    std::vector<Ptr> mChildren;
    SceneNode* mParent;
	
};