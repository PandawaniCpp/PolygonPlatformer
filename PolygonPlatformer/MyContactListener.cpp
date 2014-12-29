#include "MyContactListener.h"
#include "Player.h"

#define PIXELTOMETER (1.f/10.f)

void MyContactListener::BeginContact(b2Contact* contact){
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataAnother = contact->GetFixtureB()->GetBody()->GetUserData();


	if (bodyUserData&&bodyUserDataAnother)
	{
		SceneNode* collidingNode = static_cast<SceneNode*> (bodyUserData);
		SceneNode* collidingNodeAnother = static_cast<SceneNode*> (bodyUserDataAnother);
		collidingNode->beginContact(collidingNodeAnother);
		collidingNodeAnother->beginContact(collidingNode);
	}

}

void MyContactListener::EndContact(b2Contact* contact){
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataAnother = contact->GetFixtureB()->GetBody()->GetUserData();


	if (bodyUserData&&bodyUserDataAnother)
	{
		SceneNode* collidingNode = static_cast<SceneNode*> (bodyUserData);
		SceneNode* collidingNodeAnother = static_cast<SceneNode*> (bodyUserDataAnother);
		collidingNode->endContact(collidingNodeAnother);
		collidingNodeAnother->endContact(collidingNode);
	}
}


void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataAnother = contact->GetFixtureB()->GetBody()->GetUserData();


	if (bodyUserData&&bodyUserDataAnother)
	{
		SceneNode* collidingNode = static_cast<SceneNode*> (bodyUserData);
		SceneNode* collidingNodeAnother = static_cast<SceneNode*> (bodyUserDataAnother);
		collidingNode->preSolve(contact, collidingNodeAnother);
		collidingNodeAnother->preSolve(contact,collidingNode);
	}
}
