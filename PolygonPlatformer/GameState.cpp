#include "GameState.h"

#define PIXELTOMETER (1.f/10.f)


GameState::GameState(StateStack & stack, Game * game) : State(stack, game), doSleep(true),
timeStep (1.0f / 60.0f),
velocityIterations (6),
positionIterations (2),
soundPlayer() {

	//stateStack = &stack;
	stateID = States::GAME;
	////////////////////////////////
	//////////LOL//////////////////
	///////////////////////////////
	stateStack->gameStatePtr = this;
	
	/////////////////////////////////
	//Setting up Box2d world/////////
	/////////////////////////////////

	gravity = b2Vec2(0.f, 100.f);
	world = new b2World(gravity);
	world->SetAllowSleeping(doSleep);

	//////////////////////////////////////////
	//Initializing SceneNode static variables/
	//////////////////////////////////////////

	SceneNode::globalRoot = &root;
	SceneNode::globalWorld = world;
	SceneNode::globalQueuedForDeletion = &queuedForDeletion;
	SceneNode::globalQueuedForInsertion = &queuedForInsertion;
	SceneNode::globalTextureHolder = &textures;
	SceneNode::soundPlayer = &soundPlayer;

   
	///////////////////////////
	//Loading textures/////////
	///////////////////////////
	textures.load(Textures::ENEMY_KAMIKAZE, "./textures/enemy_kamikaze.png");
	textures.load(Textures::ENEMY_SWARM, "./textures/enemy_swarm.png");
	textures.load(Textures::ENEMY_FAT, "./textures/enemy_fat.png");
	textures.load(Textures::PLAYER_HIT, "./textures/player_hit.png");
	textures.load(Textures::HEALTHBAR_RED, "./textures/healthbar_red.png");
	textures.load(Textures::HEALTHBAR_GREEN, "./textures/healthbar_green.png");
	textures.load(Textures::PLAYER_RIGHT_ANIMATION, "./textures/player_right_tmp.png");
	textures.load(Textures::PLAYER_RIGHT, "./textures/player_right.png");
	textures.load(Textures::PLAYER_LEFT, "./textures/player_left.png");
	textures.load(Textures::FRIENDLY_BULLET, "./textures/friendly_bullet.png");
	textures.load(Textures::ENEMY_BULLET, "./textures/enemy_bullet.png");
	textures.load(Textures::GAME_BACKGROUND, "./textures/game_background.png");
	textures.load(Textures::ENEMY_FIGHTER, "./textures/enemy_fighter.png");
	textures.load(Textures::BLOOD, "./textures/blood.png");


	/////////////////////////////////
	//Setting up background//////////
	/////////////////////////////////
	root.setTexture(textures.get(Textures::GAME_BACKGROUND));
	root.setOrigin(root.getTextureRect().width / 2.f, root.getTextureRect().height / 2.f);
	root.setPosition(1120.f / 2.f, 630.f / 2.f);


	/////////////////////////////////
	//Creating Player////////////////
	/////////////////////////////////
	player = new(Player);

	Creature::currentPlayer = player;


	/////////////////////////////////
	//Setting up collisions//////////
	/////////////////////////////////
	world->SetContactListener(&myContactListenerInstance);

    
    /////////////////////////////////
    //Scene - Setup//////////////////
    /////////////////////////////////
    map = new Map(7);

    /////////////////////////////////
    //Camera - Viewport//////////////
    /////////////////////////////////
    gamePtr->view.setCenter (player->getPosition ());

	game->musicPlayer.play(Music::GAMETHEME);
}

void GameState::draw (sf::RenderTarget& target) {
    sf::Vector2u size = target.getSize ();
    gamePtr->view.setSize (size.x, size.y);
    target.setView (gamePtr->view);
    root.draw (target);
}

bool GameState::handleEvent (const sf::Event& event) {
    
        switch (event.type) {

            case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space)
					spawnEnemyFighter(rand()%800,rand()%300);
				if (event.key.code == sf::Keyboard::M)
					spawnEnemyFat(rand() % 800, rand() % 300);
				if (event.key.code == sf::Keyboard::N)
					spawnEnemySwarm(rand() % 800, rand() % 300);
				if (event.key.code == sf::Keyboard::B)
					spawnEnemyKamikaze(rand() % 800, rand() % 300);

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

	for (std::vector<SceneNode::Ptr>::iterator it = queuedForInsertion.begin(); it != queuedForInsertion.end(); ++it)
		root.attachChild(*it);
	queuedForInsertion.clear();



	for (std::vector<SceneNode *>::iterator it = queuedForDeletion.begin(); it != queuedForDeletion.end(); ++it)
		root.detachChild(*(*it));
	queuedForDeletion.clear();

	

    root.update (dt, world);
    gamePtr->view.setCenter (player->getPosition ());

	soundPlayer.removeStoppedSounds();

    return true;
}

void GameState::spawnEnemyFighter(float x, float y){
	new EnemyFighter(x,y);
}

void GameState::spawnEnemyFat(float x, float y){
	new EnemyFat(x, y);
}

void GameState::spawnEnemySwarm(float x, float y){
	for (int i = 0; i < 10;++i)
	new EnemySwarm(x, y);
}

void GameState::spawnEnemyKamikaze(float x, float y){
	new EnemyKamikaze(x, y);
}

GameState::~GameState(){
	stateStack->gameStatePtr = nullptr;
}
/*void GameState::createBot () {
    Player::Ptr tmp (new SceneNode);
    tmp->setTexture (textures.get (Textures::PLAYER_LEFT));
    root.attachChild (tmp);
    tmp->setOrigin (tmp->getTextureRect ().width / 2.f, tmp->getTextureRect ().height / 2.f);


    b2BodyDef tempBodyDef;
    tempBodyDef.type = b2_dynamicBody;
    tempBodyDef.position.Set ((rand () % 1120)*PIXELTOMETER, (rand () % 315)*PIXELTOMETER);
    tempBodyDef.angle = 0;

    b2Body* tempDynamicBody = world->CreateBody (&tempBodyDef);

    b2FixtureDef tempBoxFixtureDef;

    b2PolygonShape tempBoxShape;

    tempBoxShape.SetAsBox ((tmp->getTextureRect ().width / 2.f)*PIXELTOMETER, (tmp->getTextureRect ().height / 2.f)*PIXELTOMETER);

    tempBoxFixtureDef.shape = &boxShape;
    tempBoxFixtureDef.density = 1;
    tempBoxFixtureDef.friction = 1;

    tempDynamicBody->CreateFixture (&tempBoxFixtureDef);

    tmp->myBody = tempDynamicBody;


}*/