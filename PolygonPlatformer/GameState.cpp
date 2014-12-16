#include "GameState.h"
#define PIXELTOMETER (1.f/10.f)


GameState::GameState (StateStack & stack) : doSleep (true),
                                            player (new Player),
                                            timeStep (1.0f / 60.0f),
                                            velocityIterations (6),
                                            positionIterations (2){
	
	stateStack = &stack;
	stateID = States::GAME;
    
    gravity = b2Vec2 (0.f, 100.f);
    world = new b2World (gravity);
    root.attachChild (player);
    textures.load (Textures::PLAYER, "./textures/player.png");
    player->setTexture (textures.get (Textures::PLAYER));
    player->setOrigin (player->getTextureRect ().width / 2.f, player->getTextureRect ().height / 2.f);
    textures.load (Textures::GAME_BACKGROUND, "./textures/game_background.png");
    root.setTexture (textures.get (Textures::GAME_BACKGROUND));
    root.setOrigin (root.getTextureRect ().width / 2.f, root.getTextureRect ().height / 2.f);
    root.setPosition (1120.f / 2.f, 630.f / 2.f);
    world->SetAllowSleeping (doSleep);


    myBodyDef.type = b2_dynamicBody; 
    myBodyDef.position.Set (100.f*PIXELTOMETER, 100.f*PIXELTOMETER); 
    myBodyDef.angle = 0; 

    b2Body* dynamicBody = world->CreateBody (&myBodyDef);

    boxShape.SetAsBox ((player->getTextureRect().width/2.f)*PIXELTOMETER, (player->getTextureRect().height/2)*PIXELTOMETER );

    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    dynamicBody->CreateFixture (&boxFixtureDef);
    dynamicBody->SetFixedRotation (true);
    player->myBody = dynamicBody;
    dynamicBody->SetLinearVelocity (b2Vec2 (30.f, -10.f));

    /*groundBodyDef.position.Set ((1120.0f / 2.f)*PIXELTOMETER, 300.f*PIXELTOMETER);
    //groundBodyDef.type = b2_dynamicBody;
    b2Body* groundBody = world->CreateBody (&groundBodyDef);
   

    groundBox.SetAsBox ((1120.0f/2.f)*PIXELTOMETER, (30.0f/2.f)*PIXELTOMETER);
    groundBody->CreateFixture (&groundBox, 0.0f);

    /*SceneNode::Ptr tmp( new SceneNode);
    tmp->myBody = groundBody;
    textures.load (Textures::GROUND, "./textures/ground.png");
    tmp->setTexture (textures.get (Textures::GROUND));
    tmp->setOrigin (tmp->getTextureRect ().width / 2.f, tmp->getTextureRect ().height / 2.f);
    root.attachChild (tmp);*/

    root.attachChild (SceneNode::Ptr (new Platform ({10.f, 250.f}, {20, 1}, textures, *world)));
    root.attachChild (SceneNode::Ptr (new Platform ({500.f, 350.f}, {13, 1}, textures, *world)));
}

void GameState::draw(sf::RenderTarget& target){
    root.draw (target);
}

bool GameState::handleEvent(const sf::Event& event) {
            player->handleEvent (event);
    

	/*if (event.key.code == sf::Keyboard::Up) {
		// do shit
	}
	if (event.key.code == sf::Keyboard::Down) {
		// do other shit
	}*/
	return true;
}


bool GameState::update(sf::Time dt) {
    world->Step (timeStep, velocityIterations, positionIterations);
    root.update (dt,world);

    return true;
}