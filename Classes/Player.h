#pragma once
#include "GameObject.h"


class Player : public GameObject{
public:
	Player(b2World* world, bool secondPlayer = false);
	virtual ~Player();
	
	virtual void resolveCollision(GameObject* other);
	virtual void resolveEndCollision(GameObject* other);

	void jump();
	void moveLeft();
	void moveRight();

protected:
	cocos2d::CCSprite *sprite;
	bool isOnGround;

	virtual void setupBody();
	virtual void update(float dt);
};
