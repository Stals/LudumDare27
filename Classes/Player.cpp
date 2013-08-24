#include "Player.h"
#include "Constants.h"

Player::Player(b2World* world):GameObject(world, PlayerType)
{
	sprite = CCSprite::create("Player.png");
	this->addChild(sprite);
	this->setupBody();
	this->autorelease();
}

Player::~Player(){
	world->DestroyBody(body);
}

void Player::resolveCollision(GameObject* other){
	if(other->getType() == RockType){
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/rock_hit_ground.wav");
		//this->removeFromParentAndCleanup(true);
	}
}

void Player::setupBody(){
	b2BodyDef spriteBodyDef;
    spriteBodyDef.type = b2_dynamicBody;  //b2_staticBody - для floor and finish 
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



void Player::jump(){
	b2Vec2 force = b2Vec2(0.f, 10.0);
	b2Vec2 point = body->GetPosition();

	body->ApplyLinearImpulse(force, point);
}

void Player::moveLeft(){
	b2Vec2 currentVelocity = body->GetLinearVelocity();
	// reset velocity if we need to move in opotive side
	if(currentVelocity.x > 0){
		currentVelocity.x = 0;
	}
	body->SetLinearVelocity(currentVelocity);


	b2Vec2 force = b2Vec2(-0.5f, 0.f);
	b2Vec2 point = body->GetPosition();

	body->ApplyLinearImpulse(force, point);

}

void Player::moveRight(){
	b2Vec2 currentVelocity = body->GetLinearVelocity();
	// reset velocity if we need to move in opotive side
	if(currentVelocity.x < 0){
		currentVelocity.x = 0;
	}
	body->SetLinearVelocity(currentVelocity);

	b2Vec2 force = b2Vec2(0.5f, 0.f);
	b2Vec2 point = body->GetPosition();

	body->ApplyLinearImpulse(force, point);
}
