
#include "Pickup.h"
#include "Player.h"
#define PIXELTOMETER (1.f/10.f)


Pickup::~Pickup () {
    globalWorld->DestroyBody (myBody);


}






Pickup::Pickup (float x, float y, ObjectId::ID id) {

   
    MyId = id;

 

  

    lifespan = sf::seconds (15.f);

    if (MyId==ObjectId::PICKUP_FRENZY)
        setTexture (globalTextureHolder->get (Textures::PICKUP_FRENZY));
    else if (MyId == ObjectId::PICKUP_BLOODLUST)
        setTexture (globalTextureHolder->get (Textures::PICKUP_BLOODLUST));

    setOrigin (getTextureRect ().width / 2.f, getTextureRect ().height / 2.f);
    globalQueuedForInsertion->push_back (Ptr (this));

    //globalRoot->attachChild(Ptr(this));

    b2FixtureDef boxFixtureDef;
    b2PolygonShape boxShape;
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set (x*PIXELTOMETER, y*PIXELTOMETER);
    myBodyDef.angle = 0;
    b2Body* dynamicBody = globalWorld->CreateBody (&myBodyDef);
    boxShape.SetAsBox ((getTextureRect ().width / 2.f)*PIXELTOMETER, (getTextureRect ().height / 2.f)*PIXELTOMETER);
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.friction = 0;
    dynamicBody->CreateFixture (&boxFixtureDef);
    dynamicBody->SetUserData (this);
    myBody = dynamicBody;



    /*textures->load(Textures::HEALTHBAR_RED, "./textures/healthbar_red.png");
    textures->load(Textures::HEALTHBAR_GREEN, "./textures/healthbar_green.png");*/
   


}




void Pickup::updateCurrent (sf::Time dt, b2World* world) {

    

    if (lifespan <= sf::Time::Zero)
        lifespan = sf::Time::Zero;



   
    if (lifespan == sf::Time::Zero)
        globalQueuedForDeletion->push_back (this);

    

    setPosition (myBody->GetPosition ().x / PIXELTOMETER, myBody->GetPosition ().y / PIXELTOMETER);





}



void Pickup::beginContact (SceneNode* anotherNode) {
    if (anotherNode->MyId == ObjectId::PLAYER) {
        globalQueuedForDeletion->push_back (this);
    }
}


void Pickup::endContact (SceneNode* anotherNode) {

}

void Pickup::preSolve (b2Contact* contact, SceneNode* anotherNode) {
    if (anotherNode->MyId != ObjectId::PLAYER)
        contact->SetEnabled (false);
    if (anotherNode->MyId == ObjectId::PICKUP_FRENZY || anotherNode->MyId == ObjectId::PICKUP_BLOODLUST || anotherNode->MyId == ObjectId::PLATFORM)
        contact->SetEnabled (true);
}