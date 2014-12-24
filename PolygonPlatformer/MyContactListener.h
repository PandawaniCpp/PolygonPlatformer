#include <Box2D/Box2D.h>
#include "SceneNode.h"
class MyContactListener : public b2ContactListener{
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

};