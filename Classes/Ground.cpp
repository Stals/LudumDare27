#include "Ground.h"
#include "Constants.h"

Ground::Ground(b2World* world):GameObject(world, GroundType)
{
	sprite = CCSprite::create("Ground.png");
	this->addChild(sprite);
	this->setupBody();
}

void Ground::resolveCollision(GameObject* other){
}

void Ground::setupBody(){
	b2BodyDef spriteBodyDef;
    spriteBodyDef.type = b2_staticBody;  //b2_staticBody - для floor and finish 
    spriteBodyDef.position.Set(this->getPositionX()/PTM_RATIO, 
		this->getPositionY()/PTM_RATIO);
    spriteBodyDef.userData = this;
    body = world->CreateBody(&spriteBodyDef);
 
    b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width/PTM_RATIO/2,
                         sprite->getContentSize().height/PTM_RATIO/2);

    b2FixtureDef spriteShapeDef;
    spriteShapeDef.shape = &spriteShape;
    spriteShapeDef.density = 0.0; // so that will not spin
    spriteShapeDef.isSensor = false;
    body->CreateFixture(&spriteShapeDef);
}
