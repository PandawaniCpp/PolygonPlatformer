#include "GameState.h"

#define PIXELTOMETER (1.f/10.f)


GameState::GameState(StateStack & stack, Game * game) : State(stack, game), doSleep(true),
timeStep (1.0f / 60.0f),
velocityIterations (6),
positionIterations (2),
enemiesNumber(0), 
soundPlayer() {
	
	fighterToSpawn = 5;
	fatToSpawn = 1;
	swarmToSpawn = 1;
	kamikazeToSpawn = 3;


	//stateStack = &stack;
	stateID = States::GAME;
	////////////////////////////////
	//////////LOL//////////////////
	///////////////////////////////
	stateStack->gameStatePtr = this;
	upgrade[0] = upgrade[1] = upgrade[2] = 100;
	money = 0;
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
    textures.load (Textures::BLOOD, "./textures/blood.png");
    textures.load (Textures::GROUND, "./textures/brick.png");


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
    map = new Map (7, {32, 21});

    /////////////////////////////////
    //Camera - Viewport//////////////
    /////////////////////////////////
    gamePtr->view.setCenter (player->getPosition ());

	game->musicPlayer.play(Music::GAMETHEME);

	////////////////////////////////
	//Loading font//////////////////
	////////////////////////////////

	font.loadFromFile("./textures/coolFont.ttf");

	///////////////////////////////
	//Setting enemies counter//////
	///////////////////////////////

	enemiesCounter.setStyle(sf::Text::Italic);
	enemiesCounter.setColor(sf::Color::Red);
	enemiesCounter.setFont(font);
	enemiesOnMap << "Enemies: " << enemiesNumber;
	enemiesCounter.setString(enemiesOnMap.str());
	enemiesCounter.setCharacterSize(game->graphics.getWindowHeight() / 10);
	enemiesCounter.setPosition(sf::Vector2f(game->view.getCenter().x - (game->graphics.getWindowWidth() / 2) + 10,
		game->view.getCenter().y - (game->graphics.getWindowHeight() /2) + 10));

	///////////////////////////////
	//Setting money counter////////
	///////////////////////////////

	moneyCounter.setStyle(sf::Text::Italic);
	moneyCounter.setColor(sf::Color::Yellow);
	moneyCounter.setFont(font);
	moneyString << "Money: " << money;
	moneyCounter.setString(moneyString.str());
	moneyCounter.setCharacterSize(game->graphics.getWindowHeight() / 10);
	moneyCounter.setPosition(sf::Vector2f(game->view.getCenter().x - (game->graphics.getWindowWidth() / 2) + 10,
		game->view.getCenter().y + (game->graphics.getWindowHeight() / 2) - 10 - moneyCounter.getLocalBounds().height));


	//Help
	helpPressed = false;
	help.setStyle(sf::Text::Italic);
	help.setFont(font);
	help.setColor(sf::Color::Yellow);
	help.setString(" To move left press Left Key\n  To move right press Right Key\n To jump press Up Key\nTo shoot press K");
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(10000, 10000));
	
}

void GameState::draw (sf::RenderTarget& target) {
   
		sf::Vector2u size = target.getSize();
		gamePtr->view.setSize(size.x, size.y);
		target.setView(gamePtr->view);
		root.draw(target);
		target.draw(enemiesCounter);
		target.draw(moneyCounter);
		
		if (helpPressed)
		{
			gamePtr->gameWindow.draw(backgroundShape);
			gamePtr->gameWindow.draw(help);
		}
	
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
				if (event.key.code == sf::Keyboard::Num1)
					++enemiesNumber;
				if (event.key.code == sf::Keyboard::I)
				{
					requestStackPush(States::UPGRADE); 
					Player::me->isMovingLeft = false;
					Player::me->isMovingRight = false;
					Player::me->isShooting = false;
					Player::me->isJumping = false;
					Player::me->isAscending = false;
				}
				
				if (event.key.code == sf::Keyboard::Escape)
				{
					requestStackPush(States::PAUSE);
					Player::me->isMovingLeft = false;
					Player::me->isMovingRight = false;
					Player::me->isShooting = false;
					Player::me->isJumping = false;
					Player::me->isAscending = false;
				}
				if (event.key.code == sf::Keyboard::F1)
					helpPressed = !helpPressed;
                break;

            case sf::Event::KeyReleased:
                break;
    }
		
			player->handleEvent (event);

  
    return true;
}


bool GameState::update (sf::Time dt) {

	if (Player::me->currentHP <= 0){
		requestStackPush(States::END);
	}
	help.setCharacterSize(gamePtr->graphics.getWindowHeight() / 15);
	help.setOrigin(0, enemiesCounter.getLocalBounds().height);

	help.setPosition(gamePtr->view.getCenter().x + enemiesCounter.getLocalBounds().width, gamePtr->view.getCenter().y - enemiesCounter.getLocalBounds().height);

	if (fighterToSpawn>=0)
	while (SceneNode::fighterOnMap <= SceneNode::currentWave * 3)
	{
		if (fighterToSpawn <= 0)
			break;
		spawnEnemyFighter((rand() % 800 + 100), (rand() % 300) + 100);
		--fighterToSpawn;
	}


	if (fatToSpawn >= 0)
	while (SceneNode::fatOnMap <= SceneNode::currentWave)
	{
		if (fatToSpawn <= 0)
			break;
		spawnEnemyFat((rand() % 800 + 100), (rand() % 300) + 100);
		--fatToSpawn;
	}

	if (swarmToSpawn >= 0)
	while (SceneNode::swarmOnMap <= SceneNode::currentWave)
	{
		if (swarmToSpawn <= 0)
			break;
		spawnEnemySwarm((rand() % 800+100), (rand() % 300)+100);
		--swarmToSpawn;
	}

	if (kamikazeToSpawn >= 0)
	while (SceneNode::kamikazeOnMap <= SceneNode::currentWave )
	{
		if (kamikazeToSpawn <= 0)
			break;
		spawnEnemyKamikaze((rand() % 800 + 100), (rand() % 300) + 100);
		--kamikazeToSpawn;
	}





    world->Step (timeStep, velocityIterations, positionIterations);


	for (std::vector<SceneNode::Ptr>::iterator it = queuedForInsertion.begin(); it != queuedForInsertion.end(); ++it)
		root.attachChild(*it);
	queuedForInsertion.clear();



	for (std::vector<SceneNode *>::iterator it = queuedForDeletion.begin(); it != queuedForDeletion.end(); ++it)
		root.detachChild(*(*it));
	queuedForDeletion.clear();

	
	enemiesNumber = 0;
	enemiesNumber += SceneNode::fighterOnMap;
	enemiesNumber += SceneNode::fatOnMap;
	enemiesNumber += SceneNode::kamikazeOnMap;
	enemiesNumber += SceneNode::swarmOnMap;

    money = SceneNode::globalMoney;
	

    root.update (dt, world);


	if (enemiesNumber == 0)
	{
		++SceneNode::currentWave;
		fighterToSpawn = 5 * SceneNode::currentWave;
		fatToSpawn = SceneNode::currentWave;
		swarmToSpawn = SceneNode::currentWave;
		kamikazeToSpawn = 2 * SceneNode::currentWave;
		requestStackPush(States::UPGRADE);

	}




    gamePtr->view.setCenter (player->getPosition ());

	soundPlayer.removeStoppedSounds();

	enemiesOnMap.str(std::string());
	enemiesOnMap.clear();
	enemiesOnMap << "Enemies: " << enemiesNumber;
	enemiesCounter.setString(enemiesOnMap.str());
	enemiesCounter.setPosition(sf::Vector2f(gamePtr->view.getCenter().x - (gamePtr->graphics.getWindowWidth() / 2) + 10,
		gamePtr->view.getCenter().y - (gamePtr->graphics.getWindowHeight() / 2) + 10));

	moneyString.str(std::string());
	moneyString.clear();
	moneyString << "Money: " << money;
	moneyCounter.setString(moneyString.str());
	moneyCounter.setPosition(sf::Vector2f(gamePtr->view.getCenter().x - (gamePtr->graphics.getWindowWidth() / 2) + 10,
		gamePtr->view.getCenter().y + (gamePtr->graphics.getWindowHeight() / 2) - 10 - moneyCounter.getLocalBounds().height));

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

void GameState::setEnemiesOnMap(unsigned int number) {
	enemiesNumber = number;
}

unsigned int GameState::getEnemiesOnMap() {
	return enemiesNumber;
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