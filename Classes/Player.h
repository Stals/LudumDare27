#pragma once
#include "GameObject.h"

#define MAX_JUMPS 1

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
	int jumpsLeft;

	virtual void setupBody();
	virtual void update(float dt);
};
