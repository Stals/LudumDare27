#include "GameObject.h"
#include "Constants.h"


GameObject::GameObject(b2World* world, ObjectType type){
	CCSprite::init();

	this->world = world;
	this->objectType = type;

}

GameObject::~GameObject(){
	body->SetUserData(NULL);
}

ObjectType GameObject::getType(){
	return objectType;
}

void GameObject::setStartPosition(const CCPoint& pos){
	CCSprite::setPosition(pos);
	b2Vec2 b2Position = b2Vec2(pos.x/PTM_RATIO,
								pos.y/PTM_RATIO);

	body->SetTransform(b2Position, 0);
}


