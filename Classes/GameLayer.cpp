#include "GameLayer.h"
#include "Constants.h"
#include "Rock.h"
#include "Finish.h"


USING_NS_CC;
//#define DEBUG_BOX2D
#ifdef DEBUG_BOX2D
#include "B2DebugDraw/B2DebugDrawLayer.h"
#endif

bool GameLayer::twoPlayers = false;
bool GameLayer::firstLunch = true;

GameLayer::~GameLayer(){
	/*b2World *m_b2dWorld;
    CContactListener *m_contactListener;
	Ground* ground;
	Wall* wallLeft;
	Wall* wallRight;
	Player* player;
	Keyboard* keyboard;*/
}


CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 1337);

    // return the scene
    return scene;
}

void GameLayer::setTwoPlayers(bool twoPlayers){
	GameLayer::twoPlayers = twoPlayers;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	playerOne = NULL;
	playerTwo = NULL;
	currentGameSpeed = 1.75f;

	setupKeyboard();
	setupBackground();
	setupWorld();
	setupGround();
	setupWalls();


	setupFinish();
	setupTimer();


	setTouchEnabled(true);
    scheduleUpdate();
	schedule(schedule_selector(GameLayer::spawnRock), 0.25/1.5);
	
	if(firstLunch){
		endGame(GameOverType::None);
		firstLunch = false;
	}else{
		setupPlayer(false);
	
		if(twoPlayers){
			setupPlayer(true);
		}

		slowTime(currentGameSpeed);
	}

	//setGameSpeed(0.075f);
	
	

    return true;
}

void GameLayer::setupKeyboard(){
	keyboard = new Keyboard;
}


void GameLayer::setupWorld(){
	// Create b2 world
    //b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
	b2Vec2 gravity = b2Vec2(0.0f, -1.f);
    m_b2dWorld = new b2World(gravity);
	m_b2dWorld->SetAllowSleeping(false);
    
    // Create contact listener
    m_contactListener = new CContactListener();
    m_b2dWorld->SetContactListener(m_contactListener);
	m_b2dWorld->Step(1, 10, 10);


#ifdef DEBUG_BOX2D
	addChild(B2DebugDrawLayer::create(m_b2dWorld, PTM_RATIO), 9999);
#endif
}

void GameLayer::setupBackground(){
	CCLayerColor* bg = CCLayerColor::create(ccc4(255, 255, 255, 255));
	this->addChild(bg, zBackground);
}


void GameLayer::update(float delta )
{
   // Updates the physics simulation for 10 iterations for velocity/position
   
	m_b2dWorld->Step(delta, 10, 10);
	std::vector<b2Body*> bodiesToDestroy;

	for(b2Body *b = m_b2dWorld->GetBodyList(); b; b=b->GetNext()) {    
		if (b->GetUserData() != NULL) {
			CCSprite *ballData = (CCSprite *)b->GetUserData();
			ballData->setPositionX(b->GetPosition().x * PTM_RATIO);
			ballData->setPositionY(b->GetPosition().y * PTM_RATIO);

			//ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}else{
			bodiesToDestroy.push_back(b);
		}        
    }

	for(std::vector<b2Body*>::iterator it = bodiesToDestroy.begin(); it != bodiesToDestroy.end(); ++it){
		b2Contact* contact = (*it)->GetContactList()->contact;	
		m_b2dWorld->DestroyBody(*it);
	}

	if(playerOne){
		if(keyboard->wasKeyPressed(InputKey::Key_Up)){
			playerOne->jump();
		}
		if(keyboard->isKeyDown(InputKey::Key_Left)){
			playerOne->moveLeft();
		}
		if(keyboard->isKeyDown(InputKey::Key_Right)){
			playerOne->moveRight();
		}
	}

	if(playerTwo){
		if(keyboard->wasKeyPressed(InputKey::Key_Space) ||
			keyboard->wasKeyPressed(InputKey::Key_W)){
			playerTwo->jump();
		}
		if(keyboard->isKeyDown(InputKey::Key_A)){
			playerTwo->moveLeft();
		}
		if(keyboard->isKeyDown(InputKey::Key_D)){
			playerTwo->moveRight();
		}
	}

	if(keyboard->wasKeyPressed(InputKey::Key_R)){
		this->restart(this);		
	}


}

void GameLayer::spawnRock(float delta){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	Rock* rock = new Rock(m_b2dWorld);
	int x = (rand() % (int)winSize.width-60) + 30;
	rock->setStartPosition(ccp(x, winSize.height + 50));

	this->addChild(rock, zRock);
}

void GameLayer::setupGround(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	ground = new Ground(m_b2dWorld);
	ground->setStartPosition(ccp(winSize.width/2, 0));

	this->addChild(ground, zGround);
}

void GameLayer::setupWalls(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	wallLeft = new Wall(m_b2dWorld);
	wallRight = new Wall(m_b2dWorld);

	wallLeft->setStartPosition(ccp(0, 0));
	wallRight->setStartPosition(ccp(winSize.width, 0));

	this->addChild(wallLeft);
	this->addChild(wallRight);
}

void GameLayer::setupPlayer(bool second){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	if(!second){
		playerOne = new Player(m_b2dWorld, false);

		playerOne->setStartPosition(ccp(winSize.width/2 - 100, 90));
		this->addChild(playerOne, zPlayer);
	}else{
		playerTwo = new Player(m_b2dWorld, true);

		playerTwo->setStartPosition(ccp(winSize.width/2 + 100, 90));
		this->addChild(playerTwo, zPlayer);
	}
}

void GameLayer::setupFinish(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	Finish* finish = new Finish(m_b2dWorld);
	finish->setStartPosition(ccp(winSize.width/2, winSize.height));
	this->addChild(finish, zFinish);
}

void GameLayer::setupTimer(){
	timer = new TimerSprite(10, 32, ccc3(127, 127, 127));
	timer->setOpacity(0.5f);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	timer->setPosition(ccp(60, winSize.height-160));
	timer->setUpdateTime(1.f);
	timer->setEndTimeCallback(this, menu_selector(GameLayer::timeUp));
	this->addChild(timer, zTimer);
}

void GameLayer::timeUp(CCObject *pSender){
	endGame(GameOverType::PlayerLooseTime);
}

void GameLayer::restart(CCObject *pSender){
	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void GameLayer::endGame(GameOverType type){
	// only add one layer
	if(!this->getChildByTag(zGameOver)){

		bool show = true;

		if ((type == GameOverType::PlayerLooseRock) && twoPlayers){
			if(playerOne->isDead() && playerTwo->isDead()){
				show = true;
			}else{
				// dont show if not both player are dead
				show = false;
			}
		}
	
		if(show){
			setGameSpeed(2.f);
			schedule(schedule_selector(GameLayer::spawnRock), 0.04f);
			timer->stop();

			GameOverLayer* gameOverLayer = new GameOverLayer(type, this, menu_selector(GameLayer::startOnePlayer), menu_selector(GameLayer::startTwoPlayer));
			gameOverLayer->autorelease();

			this->addChild(gameOverLayer, zGameOver, zGameOver);
		}
	}
}


void GameLayer::setGameSpeed(float scale){
	this->currentGameSpeed = scale;

	float normalGravity = -9.8f;

	b2Vec2 gravity = b2Vec2(0.0f, normalGravity * scale);
	m_b2dWorld->SetGravity(gravity);


	float normalSpawnRate = 0.0166666;
	schedule(schedule_selector(GameLayer::spawnRock), normalSpawnRate * (1/scale));

	timer->setUpdateTime(0.1 / scale);
}

void GameLayer::slowTime(float currentTime){
	setGameSpeed(currentGameSpeed * 0.9);

	this->unschedule(schedule_selector(GameLayer::slowTime));

	if( currentGameSpeed > 0.075f){
		this->schedule(schedule_selector(GameLayer::slowTime), 0.075f);
	}
}

void GameLayer::startOnePlayer(CCObject *pSender){
	GameLayer::setTwoPlayers(false);
	restart(pSender);
}

void GameLayer::startTwoPlayer(CCObject *pSender){
	GameLayer::setTwoPlayers(true);
	restart(pSender);
}
