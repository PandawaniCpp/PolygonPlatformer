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
		ENEMY_SWARM,
		ENEMY_KAMIKAZE,
		FRIENDLY_BULLET,
		ENEMY_BULLET,
        PICKUP_FRENZY,
        PICKUP_BLOODLUST
	};
}

class Platform;



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
	virtual float getDamage(){
		return 0;
	};

    virtual void moveBrick (sf::Vector2f) {};
    virtual void moveBrickRelative (sf::Vector2f) {};
    virtual sf::Vector2f getBrickCenter (Platform *, Platform *) { return{0,0}; };


	static std::vector<SceneNode *> *globalQueuedForDeletion;
	static std::vector<Ptr> *globalQueuedForInsertion;
	static SceneNode *globalRoot;
	static b2World *globalWorld;
	static TextureHolder *globalTextureHolder;
	static SoundPlayer *soundPlayer;
	static int fighterOnMap;
	static int fatOnMap;
	static int kamikazeOnMap;
	static int swarmOnMap;
	static int currentWave;
    static int globalMoney;


	bool needsToGetDeleted;

    b2Body* myBody;
	ObjectId::ID MyId;
	

    std::vector<Ptr> mChildren;
    SceneNode* mParent;
	
};