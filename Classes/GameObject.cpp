#include "GameObject.h"
#include "Constants.h"


GameObject::GameObject(b2World* world, ObjectType type){
	CCSprite::init();

	this->world = world;
	this->objectType = type;

	this->scheduleUpdate();
}

GameObject::~GameObject(){
}

ObjectType GameObject::getType(){
	return objectType;
}

void GameObject::setPosition(const CCPoint& pos){
	CCSprite::setPosition(pos);
	b2Vec2 b2Position = b2Vec2(pos.x/PTM_RATIO,
								pos.y/PTM_RATIO);

	body->SetTransform(b2Position, 0);
}



void GameObject::update(float dt){
	b2Vec2 newPos = body->GetPosition();

	this->setPositionX(newPos.x * PTM_RATIO);
	this->setPositionY(newPos.y * PTM_RATIO);
}
