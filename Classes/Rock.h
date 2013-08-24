#pragma once
#include "GameObject.h"

class Rock : public GameObject{
public:
	Rock(b2World* world);
	virtual ~Rock();
	
	virtual void resolveCollision(GameObject* other);

protected:
	virtual void setupBody();
};

