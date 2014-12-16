#include "GameState.h"
#define PIXELTOMETER (1.f/10.f)


GameState::GameState (StateStack & stack) : doSleep (true),
player (new Player),
timeStep (1.0f / 60.0f),
velocityIterations (6),
positionIterations (2) {

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

    boxShape.SetAsBox ((player->getTextureRect ().width / 2.f)*PIXELTOMETER, (player->getTextureRect ().height / 2)*PIXELTOMETER);

    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.friction = 0;
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
    root.attachChild (SceneNode::Ptr (new Platform ({500.f, 350.f}, {13, 2}, textures, *world)));


    /////////////////////////////////
    //Camera - Viewport//////////////
    /////////////////////////////////
    view.setCenter (player->getPosition ());
}

void GameState::draw (sf::RenderTarget& target) {
    sf::Vector2u size = target.getSize ();
    view.setSize (size.x, size.y);
    target.setView (view);
    root.draw (target);
}

bool GameState::handleEvent (const sf::Event& event) {
    
        switch (event.type) {

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space)
                    createBot ();
                break;

            case sf::Event::KeyReleased:
                break;
    }
    player->handleEvent (event);


    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {

        requestStackPush (States::PAUSE);
    }


    return true;
}


bool GameState::update (sf::Time dt) {
    world->Step (timeStep, velocityIterations, positionIterations);
    root.update (dt, world);
    view.setCenter (player->getPosition ());

    return true;
}

void GameState::createBot () {
    Player::Ptr tmp (new SceneNode);
    tmp->setTexture (textures.get (Textures::PLAYER));
    root.attachChild (tmp);
    tmp->setOrigin (tmp->getTextureRect ().width / 2.f, tmp->getTextureRect ().height / 2.f);


    b2BodyDef tempBodyDef;
    tempBodyDef.type = b2_dynamicBody;
    tempBodyDef.position.Set ((rand () % 1120)*PIXELTOMETER, (rand () % 315)*PIXELTOMETER);
    tempBodyDef.angle = 0;

    b2Body* tempDynamicBody = world->CreateBody (&tempBodyDef);

    b2FixtureDef tempBoxFixtureDef;

    b2PolygonShape tempBoxShape;

    tempBoxShape.SetAsBox ((tmp->getTextureRect ().width / 2.f)*PIXELTOMETER, (tmp->getTextureRect ().height / 2)*PIXELTOMETER);

    tempBoxFixtureDef.shape = &boxShape;
    tempBoxFixtureDef.density = 1;
    tempBoxFixtureDef.friction = 1;

    tempDynamicBody->CreateFixture (&tempBoxFixtureDef);

    tmp->myBody = tempDynamicBody;


}