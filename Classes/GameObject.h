#pragma once

#include "../external/Box2D/Box2D.h"
#include "cocos2d.h"

enum ObjectType{
	RockType,
	PlayerType,
	GroundType,
	FinishType
};


class GameObject : public cocos2d::CCSprite{
public:
	GameObject(b2World* world, ObjectType type);
	virtual ~GameObject();

	ObjectType getType();

	virtual void resolveCollision(GameObject* other) = 0;

	virtual void setPosition(const cocos2d::CCPoint& pos);
protected:
	ObjectType objectType;
	b2Body* body;
	b2World* world;

	virtual void setupBody() = 0;

	virtual void update(float dt);
};
