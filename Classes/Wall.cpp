#include "Wall.h"
#include "Constants.h"

Wall::Wall(b2World* world):GameObject(world, WallType)
{
	this->setupBody();
}

void Wall::resolveCollision(GameObject* other){
}

void Wall::setupBody(){
	b2BodyDef spriteBodyDef;
    spriteBodyDef.type = b2_staticBody;  //b2_staticBody - для floor and finish 
    spriteBodyDef.position.Set(this->getPositionX()/PTM_RATIO, 
		this->getPositionY()/PTM_RATIO);
    spriteBodyDef.userData = this;
    body = world->CreateBody(&spriteBodyDef);
 
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	b2EdgeShape spriteShape;

	const float x = winSize.width / PTM_RATIO ;
	const float y = winSize.height / PTM_RATIO;
	spriteShape.Set(b2Vec2(0, y), b2Vec2(0, 0));

    b2FixtureDef spriteShapeDef;
    spriteShapeDef.shape = &spriteShape;
    spriteShapeDef.density = 0.0; // so that will not spin
    spriteShapeDef.isSensor = false;
    body->CreateFixture(&spriteShapeDef);
}
