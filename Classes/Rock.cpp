#include "Rock.h"
#include "Constants.h"

Rock::Rock(b2World* world):GameObject(world, RockType)
{
	this->addChild(CCSprite::create("Rock.png"));
	this->setupBody();
	this->autorelease();
}

Rock::~Rock(){
	world->DestroyBody(body);
}

void Rock::resolveCollision(GameObject* other){
	if(other->getType() == GroundType){
		this->removeFromParentAndCleanup(true);
	}
}

void Rock::setupBody(){
	b2BodyDef spriteBodyDef;
    spriteBodyDef.type = b2_dynamicBody;  //b2_staticBody - для floor and finish 
    spriteBodyDef.position.Set(this->getPositionX()/PTM_RATIO, 
		this->getPositionY()/PTM_RATIO);
    spriteBodyDef.userData = this;
    body = world->CreateBody(&spriteBodyDef);
 
    b2PolygonShape spriteShape;
	b2Vec2 vertices[3];
	vertices[0].Set(-0.5,  0.5);
	vertices[1].Set(0, -0.5);
	vertices[2].Set(0.5, 0.5);
	
	spriteShape.Set(vertices, 3);

    b2FixtureDef spriteShapeDef;
    spriteShapeDef.shape = &spriteShape;
    spriteShapeDef.density = 0.0; // so that will not spin
    spriteShapeDef.isSensor = false;
    body->CreateFixture(&spriteShapeDef);
}
