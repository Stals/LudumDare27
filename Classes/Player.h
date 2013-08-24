#pragma once
#include "GameObject.h"

class Player : public GameObject{
public:
	Player(b2World* world);
	virtual ~Player();
	
	virtual void resolveCollision(GameObject* other);

protected:
	cocos2d::CCSprite *sprite;

	virtual void setupBody();
};

