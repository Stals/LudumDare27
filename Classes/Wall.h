#pragma once
#include "GameObject.h"

class Wall : public GameObject{
public:
	Wall(b2World* world);

	virtual void resolveCollision(GameObject* other);

protected:
	virtual void setupBody();
};
