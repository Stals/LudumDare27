#include "GameLayer.h"
#include "Constants.h"
#include "Rock.h"
#include "Ground.h"
#include "Player.h"

//#include "SimpleAudioEngine.h"
USING_NS_CC;
#define DEBUG_BOX2D
#ifdef DEBUG_BOX2D
#include "B2DebugDraw/B2DebugDrawLayer.h"
#endif


CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
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

	setupBackground();
	setupWorld();
	setupGround();
	setupPlayer();
	setupFinish();
	setupTimer();


	setTouchEnabled(true);
    scheduleUpdate();
	schedule(schedule_selector(GameLayer::spawnRock), 0.25);
	spawnRock(0);
    return true;
}


void GameLayer::setupWorld(){
	// Create b2 world
    b2Vec2 gravity = b2Vec2(0.0f, -10.0f); // Gravity is zero as we aren't using it, zero turns it off so no processor time wasted.
    m_b2dWorld = new b2World(gravity);
	m_b2dWorld->SetAllowSleeping(false);
    
    // Create contact listener
    m_contactListener = new CContactListener();
    m_b2dWorld->SetContactListener(m_contactListener);


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
	}

void GameLayer::spawnRock(float delta){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	Rock* rock = new Rock(m_b2dWorld);
	int x = (rand() % (int)winSize.width);
	rock->setPosition(ccp(x, winSize.height + 50));

	this->addChild(rock, zRock);
}

void GameLayer::setupGround(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	Ground* ground = new Ground(m_b2dWorld);
	ground->setPosition(ccp(winSize.width/2, 0));

	this->addChild(ground, zGround);
}

void GameLayer::setupPlayer(){

}

void GameLayer::setupFinish(){

}

void GameLayer::setupTimer(){

}

void GameLayer::restart(){
	CCScene *pScene = GameLayer::scene();
	CCDirector::sharedDirector()->runWithScene(pScene);
}
