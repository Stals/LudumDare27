#pragma once
#include "GameObject.h"

class Ground : public GameObject{
public:
	Ground(b2World* world);

	virtual void resolveCollision(GameObject* other);

protected:
	cocos2d::CCSprite *sprite;

	virtual void setupBody();
};
