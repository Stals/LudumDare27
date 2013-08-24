#pragma once
#include "GameObject.h"

class Finish : public GameObject{
public:
	Finish(b2World* world);

	virtual void resolveCollision(GameObject* other);

protected:
	cocos2d::CCSprite *sprite;

	virtual void setupBody();
};
