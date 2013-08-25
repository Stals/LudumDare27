#pragma once

#include "cocos2d.h"
using namespace cocos2d;

#include "../external/Box2D/Box2D.h"
#include "ContactListener.h"

#include "Ground.h"
#include "Player.h"
#include "Keyboard.h"
#include "Wall.h"
#include "GameOverLayer.h"
#include "Timer.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	~GameLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	void update(float dt);	

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();   

	void endGame(GameOverType type);

private:
	b2World *m_b2dWorld;
    CContactListener *m_contactListener;
	Ground* ground;
	Wall* wallLeft;
	Wall* wallRight;
	Player* player;
	Keyboard* keyboard;
	TimerSprite* timer;

	void setupKeyboard();
	void setupWorld();
	void setupBackground();
	void spawnRock(float delta);
	void setupGround();
	void setupWalls();
	void setupPlayer();
	void setupFinish();
	void setupTimer();

    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

	void timeUp(CCObject *pSender);
	void restart(CCObject *pSender);

	// 1 - full speed 0.1 - 1/10 of normal speed
	void setGameSpeed(float scale);
};


