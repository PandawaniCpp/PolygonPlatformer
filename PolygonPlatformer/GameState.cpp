#include "GameState.h"

#define PIXELTOMETER (1.f/10.f)


GameState::GameState(StateStack & stack, Game * game) : State(stack, game), doSleep(true),
timeStep(1.0f / 60.0f),
velocityIterations(6),
positionIterations(2),
enemiesNumber(0),
ready(false),
soundPlayer () {

    for (int i = 0; i < 4; i++)
        upgradeCounter[i] = 0;

    fighterToSpawn = 6;
    fatToSpawn = 0;
    swarmToSpawn = 0;
    kamikazeToSpawn = 0;
    spawnCooldown = sf::seconds (50.f);


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

    gravity = b2Vec2 (0.f, 100.f);
    world = new b2World (gravity);
    world->SetAllowSleeping (doSleep);

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
    textures.load (Textures::ENEMY_KAMIKAZE, "./textures/enemy_kamikaze.png");
    textures.load (Textures::ENEMY_SWARM, "./textures/enemy_swarm.png");
    textures.load (Textures::ENEMY_FAT, "./textures/enemy_fat.png");
    textures.load (Textures::PLAYER_HIT, "./textures/player_hit.png");
    textures.load (Textures::HEALTHBAR_RED, "./textures/healthbar_red.png");
    textures.load (Textures::HEALTHBAR_GREEN, "./textures/healthbar_green.png");
    textures.load (Textures::PLAYER_RIGHT_ANIMATION, "./textures/player_right_tmp.png");
    textures.load (Textures::PLAYER_RIGHT, "./textures/player_right.png");
    textures.load (Textures::PLAYER_LEFT, "./textures/player_left.png");
    textures.load (Textures::FRIENDLY_BULLET, "./textures/friendly_bullet.png");
    textures.load (Textures::ENEMY_BULLET, "./textures/enemy_bullet.png");
    textures.load (Textures::GAME_BACKGROUND, "./textures/game_background.png");
    textures.load (Textures::ENEMY_FIGHTER, "./textures/enemy_fighter.png");
    textures.load (Textures::BLOOD, "./textures/blood.png");
    textures.load (Textures::GROUND, "./textures/brick.png");

    /////////////////////////////////
    //Scene - Setup//////////////////
    /////////////////////////////////
    //List of variables:
    //number of places of spawn (not working yet)
    //size of map (in bricks)
    //number of platforms
    //size of biggest platform
    //size of smallest platformz
    //minimal distance between platforms
    map = new Map (7, {70, 45}, 40, {15, 1}, {7, 1}, 80.f);

    /////////////////////////////////
    //Setting up background//////////
    /////////////////////////////////
    //root.setTexture (textures.get (Textures::GAME_BACKGROUND));
    root.setOrigin (0.f, 0.f);
    root.setPosition (0.f, 0.f);


    /////////////////////////////////
    //Creating Player////////////////
    /////////////////////////////////
    player = new(Player);

    Creature::currentPlayer = player;


    /////////////////////////////////
    //Setting up collisions//////////
    /////////////////////////////////
    world->SetContactListener (&myContactListenerInstance);

    /////////////////////////////////
    //Camera - Viewport//////////////
    /////////////////////////////////
    gamePtr->view.setCenter (player->getPosition ());

    game->musicPlayer.play (Music::GAMETHEME);

    ////////////////////////////////
    //Loading font//////////////////
    ////////////////////////////////

    font.loadFromFile ("./textures/coolFont.ttf");

    ///////////////////////////////
    //Setting enemies counter//////
    ///////////////////////////////

    enemiesCounter.setStyle (sf::Text::Italic);
    enemiesCounter.setColor (sf::Color::Red);
    enemiesCounter.setFont (font);
    enemiesOnMap << "Enemies: " << enemiesNumber;
    enemiesCounter.setString (enemiesOnMap.str ());
    enemiesCounter.setCharacterSize (game->graphics.getWindowHeight () / 10);
    enemiesCounter.setPosition (sf::Vector2f (game->view.getCenter ().x - (game->graphics.getWindowWidth () / 2) + 10,
        game->view.getCenter ().y - (game->graphics.getWindowHeight () / 2) + 10));


    for (int i = 0; i < 3; i++) {

        playerInformation[i].setStyle (sf::Text::Italic);
        playerInformation[i].setColor (sf::Color::Red);
        playerInformation[i].setFont (font);
        playerInformation[i].setCharacterSize (game->graphics.getWindowHeight () / 20);
    }
    playerInformation[0].setString ("HP: " + std::to_string (Player::me->currentHP) + "/" + std::to_string (Player::me->maxHP));
    playerInformation[1].setString ("DMG: " + std::to_string (Player::me->bulletDamageVar));
    playerInformation[2].setString ("Cannibalism: " + std::to_string (Player::me->hpPerMob));

    playerInformation[0].setPosition (sf::Vector2f (gamePtr->view.getCenter ().x + (gamePtr->graphics.getWindowWidth () / 2) - 250,
        gamePtr->view.getCenter ().y + (gamePtr->graphics.getWindowHeight () / 2) - 180));
    playerInformation[1].setPosition (sf::Vector2f (gamePtr->view.getCenter ().x + (gamePtr->graphics.getWindowWidth () / 2) - 250,
        gamePtr->view.getCenter ().y + (gamePtr->graphics.getWindowHeight () / 2) - 120));
    playerInformation[2].setPosition (sf::Vector2f (gamePtr->view.getCenter ().x + (gamePtr->graphics.getWindowWidth () / 2) - 250,
        gamePtr->view.getCenter ().y + (gamePtr->graphics.getWindowHeight () / 2) - 60));



    waveCounter.setStyle (sf::Text::Italic);
    waveCounter.setColor (sf::Color::Red);
    waveCounter.setFont (font);
    waveString << "Wave: " << SceneNode::currentWave;
    waveCounter.setString (waveString.str ());
    waveCounter.setCharacterSize (game->graphics.getWindowHeight () / 10);
    waveCounter.setPosition (sf::Vector2f (game->view.getCenter ().x + (game->graphics.getWindowWidth () / 2) - 10,
        game->view.getCenter ().y - (game->graphics.getWindowHeight () / 2) + 10));

    ///////////////////////////////
    //Setting money counter////////
    ///////////////////////////////

    moneyCounter.setStyle (sf::Text::Italic);
    moneyCounter.setColor (sf::Color::Yellow);
    moneyCounter.setFont (font);
    moneyString << "Money: " << money;
    moneyCounter.setString (moneyString.str ());
    moneyCounter.setCharacterSize (game->graphics.getWindowHeight () / 10);
    moneyCounter.setPosition (sf::Vector2f (game->view.getCenter ().x - (game->graphics.getWindowWidth () / 2) + 10,
        game->view.getCenter ().y + (game->graphics.getWindowHeight () / 2) - 10 - moneyCounter.getLocalBounds ().height));


    //Help
    helpPressed = false;
    help.setStyle (sf::Text::Italic);
    help.setFont (font);
    help.setColor (sf::Color::Yellow);
    help.setString (" To move left press A\n  To move right press D\n To jump press W\nTo shoot press K");
    backgroundShape.setFillColor (sf::Color (0, 0, 0, 150));
    backgroundShape.setSize (sf::Vector2f (10000, 10000));

	readyText.setStyle(sf::Text::Italic);
	readyText.setColor(sf::Color::Red);
	readyText.setFont(font);
	readyText.setString("Press space when ready to fight");
	readyText.setCharacterSize(game->graphics.getWindowHeight() / 8);
	readyText.setOrigin(sf::Vector2f(readyText.getLocalBounds().width / 2, readyText.getLocalBounds().height / 2));
	readyText.setPosition(sf::Vector2f(game->view.getCenter().x,
		game->view.getCenter().y - game->graphics.getWindowHeight() / 3));
    //gameBackground = new SceneNode ();
   // gameBackground->setTexture (textures.get (Textures::GAME_BACKGROUND));

    //root.setScale (sf::Vector2f(0.75,0.75));
}

void GameState::draw (sf::RenderTarget& target) {
    //gamePtr->gameWindow.draw (*gameBackground);
    sf::Vector2u size = target.getSize ();
    gamePtr->view.setSize (size.x, size.y);
    target.setView (gamePtr->view);
    root.draw (target);
    target.draw (enemiesCounter);
    target.draw (moneyCounter);
    target.draw (waveCounter);
	if (!ready)
		target.draw(readyText);
    target.draw (playerInformation[0]);
    target.draw (playerInformation[1]);
    target.draw (playerInformation[2]);


    if (helpPressed) {
        //gamePtr->gameWindow.draw (backgroundShape);
       
        gamePtr->gameWindow.draw (help);
    }

}

bool GameState::handleEvent (const sf::Event& event) {
    switch (event.type) {

        case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Space) {
				spawnCooldown = sf::Time::Zero;
				ready = true;
				//spawnEnemyFighter (rand () % 800, rand () % 300);
			}
            if (event.key.code == sf::Keyboard::M)
               // spawnEnemyFat (rand () % 800, rand () % 300);
            if (event.key.code == sf::Keyboard::N)
               // spawnEnemySwarm (rand () % 800, rand () % 300);
            if (event.key.code == sf::Keyboard::B)
               // spawnEnemyKamikaze (rand () % 800, rand () % 300);
            if (event.key.code == sf::Keyboard::Num1)
               // ++enemiesNumber;
            if (event.key.code == sf::Keyboard::I) {
                /*requestStackPush (States::UPGRADE);
                Player::me->isMovingLeft = false;
                Player::me->isMovingRight = false;
                Player::me->isShooting = false;
                Player::me->isJumping = false;
                Player::me->isAscending = false;*/
            }

            if (event.key.code == sf::Keyboard::Escape) {
                requestStackPush (States::PAUSE);
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
    //\gameBackground->setPosition (gamePtr->view.getCenter ().x - gamePtr->view.getSize ().x / 2.f - 30.f, gamePtr->view.getCenter ().y - gamePtr->view.getSize ().y / 2.f - 30.f);
    spawnCooldown -= dt;

    if (spawnCooldown <= sf::Time::Zero)
        spawnCooldown = sf::Time::Zero;



    if (Player::me->currentHP <= 0) {
        SceneNode::globalMoney = 0;
        requestStackPush(States::END);
    }
    help.setCharacterSize (gamePtr->graphics.getWindowHeight () / 15);
    help.setOrigin (0, enemiesCounter.getLocalBounds ().height);

    help.setPosition (gamePtr->view.getCenter ().x + enemiesCounter.getLocalBounds ().width, gamePtr->view.getCenter ().y - enemiesCounter.getLocalBounds ().height);


    if (spawnCooldown <= sf::Time::Zero) {

        
        float x = (rand () % 2200 + 100);
        float y = (rand () % 1100 + 100);
       
        b2Vec2 distance = b2Vec2 (x*PIXELTOMETER, y*PIXELTOMETER);

        while ((distance - Player::me->myBody->GetPosition ()).LengthSquared() <= 6400)  {
            x = (rand () % 2200 + 100);
            y = (rand () % 1100 + 100);
            distance.x = x*PIXELTOMETER;
            distance.y = y*PIXELTOMETER;
}


        if (fighterToSpawn >= 0)
        while ( SceneNode::fighterOnMap < ((SceneNode::currentWave/2)+3)) {
            if (fighterToSpawn <= 0)
                break;
            while ((distance - Player::me->myBody->GetPosition ()).LengthSquared () <= 6400) {
                x = (rand () % 2200 + 100);
                y = (rand () % 1100 + 100);
                distance.x = x*PIXELTOMETER;
                distance.y = y*PIXELTOMETER;
            }
            spawnEnemyFighter (x, y);
            x = (rand () % 2200 + 100);
            y = (rand () % 1100 + 100);
            --fighterToSpawn;
            spawnCooldown += sf::seconds (1.f / 2.f);
            break;
        }


        if (fatToSpawn >= 0)
        while (SceneNode::fatOnMap < (((SceneNode::currentWave-1)/2)+1)) {
            if (fatToSpawn <= 0)
                break;
            while ((distance - Player::me->myBody->GetPosition ()).LengthSquared () <= 6400) {
                x = (rand () % 2200 + 100);
                y = (rand () % 1100 + 100);
                distance.x = x*PIXELTOMETER;
                distance.y = y*PIXELTOMETER;
            }
            spawnEnemyFat (x, y);
            x = (rand () % 2200 + 100);
            y = (rand () % 1100 + 100);
            --fatToSpawn;
            spawnCooldown += sf::seconds (1.f / 2.f);
            break;
        }

        if (swarmToSpawn >= 0)
        while ((SceneNode::swarmOnMap+5)/10 < (SceneNode::currentWave/2)) {
            if (swarmToSpawn <= 0)
                break;
            while ((distance - Player::me->myBody->GetPosition ()).LengthSquared () <= 6400) {
                x = (rand () % 2200 + 100);
                y = (rand () % 1100 + 100);
                distance.x = x*PIXELTOMETER;
                distance.y = y*PIXELTOMETER;
            }
            spawnEnemySwarm (x, y);
            x = (rand () % 2200 + 100);
            y = (rand () % 1100 + 100);
            --swarmToSpawn;
            spawnCooldown += sf::seconds (1.f / 2.f);
            break;
        }

        if (kamikazeToSpawn >= 0)
        while (SceneNode::kamikazeOnMap < ((SceneNode::currentWave-1)/3)) {
            if (kamikazeToSpawn <= 0)
                break;
            while ((distance - Player::me->myBody->GetPosition ()).LengthSquared () <= 6400) {
                x = (rand () % 2200 + 100);
                y = (rand () % 1100 + 100);
                distance.x = x*PIXELTOMETER;
                distance.y = y*PIXELTOMETER;
            }
            spawnEnemyKamikaze (x, y);
            x = (rand () % 2200 + 100);
            y = (rand () % 1100 + 100);
            --kamikazeToSpawn;
            spawnCooldown += sf::seconds (1.f / 2.f);
            break;
        }

    }



    world->Step (timeStep, velocityIterations, positionIterations);


    for (std::vector<SceneNode::Ptr>::iterator it = queuedForInsertion.begin (); it != queuedForInsertion.end (); ++it)
        root.attachChild (*it);
    queuedForInsertion.clear ();



    for (std::vector<SceneNode *>::iterator it = queuedForDeletion.begin (); it != queuedForDeletion.end (); ++it)
        root.detachChild (*(*it));
    queuedForDeletion.clear ();


    enemiesNumber = 0;
    enemiesNumber += SceneNode::fighterOnMap;
    enemiesNumber += SceneNode::fatOnMap;
    enemiesNumber += SceneNode::kamikazeOnMap;
    enemiesNumber += SceneNode::swarmOnMap;

    


    money = SceneNode::globalMoney;


    root.update (dt, world);


    if (spawnCooldown <= sf::Time::Zero) {

        if (enemiesNumber == 0) {


            spawnCooldown = sf::seconds (2);
            Player::me->isMovingLeft = false;
            Player::me->isMovingRight = false;
            Player::me->isShooting = false;
            Player::me->isJumping = false;
            Player::me->isAscending = false;



            ++SceneNode::currentWave;

            fighterToSpawn = 6;
            for (int k = 0; k < SceneNode::currentWave ; ++k)
                fighterToSpawn +=  (k+1);
            fighterToSpawn--;


            if (SceneNode::currentWave < 3) {
                fatToSpawn = 0;
            }
            else
               fatToSpawn =  (SceneNode::currentWave+1)/2;

           

            

            if (SceneNode::currentWave < 5) {
                swarmToSpawn = 0;
            }
            else
                swarmToSpawn =  (SceneNode::currentWave-5)*2 +1;


            if (SceneNode::currentWave < 7) {
                kamikazeToSpawn = 0;
            }
            else
                kamikazeToSpawn =  (SceneNode::currentWave-6)*3 -1;





            requestStackPush (States::UPGRADE);

        }
    }




    gamePtr->view.setCenter (player->getPosition ());

    soundPlayer.removeStoppedSounds ();

    enemiesOnMap.str (std::string ());
    enemiesOnMap.clear ();
    enemiesOnMap << "Enemies: " << enemiesNumber;
    enemiesCounter.setString (enemiesOnMap.str ());
    enemiesCounter.setPosition (sf::Vector2f (gamePtr->view.getCenter ().x - (gamePtr->graphics.getWindowWidth () / 2) + 10,
        gamePtr->view.getCenter ().y - (gamePtr->graphics.getWindowHeight () / 2) + 10));

    moneyString.str (std::string ());
    moneyString.clear ();
    moneyString << "Money: " << money;
    moneyCounter.setString (moneyString.str ());
    moneyCounter.setPosition (sf::Vector2f (gamePtr->view.getCenter ().x - (gamePtr->graphics.getWindowWidth () / 2) + 10,
        gamePtr->view.getCenter ().y + (gamePtr->graphics.getWindowHeight () / 2) - 10 - moneyCounter.getLocalBounds ().height));

    
    waveString.str (std::string ());
    waveString.clear ();
    waveString << "Wave: " << SceneNode::currentWave;
    waveCounter.setString (waveString.str ());
    waveCounter.setPosition (sf::Vector2f (gamePtr->view.getCenter ().x + (gamePtr->graphics.getWindowWidth () / 2) - 250,
        gamePtr->view.getCenter ().y - (gamePtr->graphics.getWindowHeight () / 2) + 10));

	readyText.setPosition(sf::Vector2f(gamePtr->view.getCenter().x,
		gamePtr->view.getCenter().y - gamePtr->graphics.getWindowHeight() / 3));


    playerInformation[0].setString ("HP: " + std::to_string (static_cast<int>(Player::me->currentHP)) + " / " + std::to_string (static_cast<int>(Player::me->maxHP)));
    playerInformation[1].setString ("DMG: " + std::to_string (static_cast<int>(Player::me->bulletDamageVar)));
    playerInformation[2].setString ("Cannibalism: " + std::to_string (static_cast<int>(Player::me->hpPerMob)));
    playerInformation[0].setColor (sf::Color (((Player::me->maxHP - Player::me->currentHP) / Player::me->maxHP) * 255, ((Player::me->currentHP) / Player::me->maxHP) * 255, 0, 255));

    playerInformation[0].setPosition (sf::Vector2f (gamePtr->view.getCenter ().x + (gamePtr->graphics.getWindowWidth () / 2) - 250,
        gamePtr->view.getCenter ().y + (gamePtr->graphics.getWindowHeight () / 2) - 180));
    playerInformation[1].setPosition (sf::Vector2f (gamePtr->view.getCenter ().x + (gamePtr->graphics.getWindowWidth () / 2) - 250,
        gamePtr->view.getCenter ().y + (gamePtr->graphics.getWindowHeight () / 2) - 120));
    playerInformation[2].setPosition (sf::Vector2f (gamePtr->view.getCenter ().x + (gamePtr->graphics.getWindowWidth () / 2) - 250,
        gamePtr->view.getCenter ().y + (gamePtr->graphics.getWindowHeight () / 2) - 60));



    return true;
}

void GameState::spawnEnemyFighter (float x, float y) {
    new EnemyFighter (x, y);
}

void GameState::spawnEnemyFat (float x, float y) {
    new EnemyFat (x, y);
}

void GameState::spawnEnemySwarm (float x, float y) {
    for (int i = 0; i < 10; ++i)
        new EnemySwarm (x, y);
}

void GameState::spawnEnemyKamikaze (float x, float y) {
    new EnemyKamikaze (x, y);
}

GameState::~GameState () {
    stateStack->gameStatePtr = nullptr;
}

void GameState::setEnemiesOnMap (unsigned int number) {
    enemiesNumber = number;
}

unsigned int GameState::getEnemiesOnMap () {
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