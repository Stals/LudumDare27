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

	bool isDead();

protected:
	cocos2d::CCSprite *sprite;
	int groundObjectsTouching;

	virtual void setupBody();
	virtual void update(float dt);

	bool spikeIntercect(GameObject* other);
};
