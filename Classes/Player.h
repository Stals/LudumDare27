#pragma once
#include "GameObject.h"

class Player : public GameObject{
public:
	Player(b2World* world);
	virtual ~Player();
	
	virtual void resolveCollision(GameObject* other);

	void jump();
	void moveLeft();
	void moveRight();

protected:
	cocos2d::CCSprite *sprite;

	virtual void setupBody();
};

