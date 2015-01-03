#pragma once
#include <memory>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "TextureHolder.h"
#include "SoundPlayer.h"


namespace ObjectId
{
	enum ID{
		PLAYER,
		PLATFORM,
		ENEMY_FIGHTER,
		ENEMY_FAT,
		FRIENDLY_BULLET,
		ENEMY_BULLET
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
	virtual void preSolve(b2Contact* contact, SceneNode* anotherNode){};

	static std::vector<SceneNode *> *globalQueuedForDeletion;
	static std::vector<Ptr> *globalQueuedForInsertion;
	static SceneNode *globalRoot;
	static b2World *globalWorld;
	static TextureHolder *globalTextureHolder;
	static SoundPlayer *soundPlayer;
	bool needsToGetDeleted;

    b2Body* myBody;
	ObjectId::ID MyId;
	
protected:
    std::vector<Ptr> mChildren;
    SceneNode* mParent;
	
};