#include "Finish.h"
#include "Constants.h"

Finish::Finish(b2World* world):GameObject(world, FinishType)
{
	sprite = CCSprite::create("Finish.png");
	this->addChild(sprite);
	this->setupBody();
}

void Finish::resolveCollision(GameObject* other){
}

void Finish::setupBody(){
	b2BodyDef spriteBodyDef;
    spriteBodyDef.type = b2_staticBody; 
    spriteBodyDef.position.Set(this->getPositionX()/PTM_RATIO, 
		this->getPositionY()/PTM_RATIO);
    spriteBodyDef.userData = this;
    body = world->CreateBody(&spriteBodyDef);
 
	
    b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width/PTM_RATIO/2,
                         sprite->getContentSize().height/PTM_RATIO/2);
	
    b2FixtureDef spriteShapeDef;
    spriteShapeDef.shape = &spriteShape;
    spriteShapeDef.density = 0.0;
    spriteShapeDef.isSensor = true;
    body->CreateFixture(&spriteShapeDef);
}
