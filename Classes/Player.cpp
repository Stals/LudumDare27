#include "Player.h"
#include "Constants.h"
#include "GameLayer.h"
#include "Rock.h"

Player::Player(b2World* world, bool secondPlayer):GameObject(world, PlayerType), groundObjectsTouching(0)
{
	if(!secondPlayer){
		sprite = CCSprite::create("Player.png");
	}else{
		sprite = CCSprite::create("Player2.png");
	}


	this->addChild(sprite);
	this->setupBody();
	this->autorelease();

	this->scheduleUpdate();
}

Player::~Player(){
	//world->DestroyBody(body);
}

void Player::resolveCollision(GameObject* other){
	if(other->getType() == RockType){
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/rock_hit_ground.wav");
		//this->removeFromParentAndCleanup(true);
	}

	switch(other->getType()){
		case RockType: 
			if(spikeIntercect(other)){
				this->body->SetUserData(NULL);
				this->sprite->setVisible(false);
				((GameLayer*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1337))->endGame(PlayerLooseRock);
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/hurt.wav");
				break;
			}
		case GroundType:
		case PlayerType:
			++groundObjectsTouching;
			break;
		case FinishType:
			this->body->SetUserData(NULL);
			this->sprite->setVisible(false);
			((GameLayer*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1337))->endGame(PlayerWin);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/win.wav");
			break;
		default:
			;
	}
}

void Player::resolveEndCollision(GameObject* other){
	switch(other->getType()){
		case RockType: 
		case GroundType:
		case PlayerType:
			if(groundObjectsTouching > 0){
			--groundObjectsTouching;
			}
	}
}

void Player::setupBody(){
	b2BodyDef spriteBodyDef;
    spriteBodyDef.type = b2_dynamicBody;  //b2_staticBody - для floor and finish 
    spriteBodyDef.position.Set(this->getPositionX()/PTM_RATIO, 
		this->getPositionY()/PTM_RATIO);
    spriteBodyDef.userData = this;
    body = world->CreateBody(&spriteBodyDef);
 
    /*b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width/PTM_RATIO/2,
                         sprite->getContentSize().height/PTM_RATIO/2);
	*/
	b2CircleShape spriteShape;
	spriteShape.m_radius = 15.f/PTM_RATIO;

    b2FixtureDef spriteShapeDef;
    spriteShapeDef.shape = &spriteShape;
    spriteShapeDef.density = 0.0; // so that will not spin
    spriteShapeDef.isSensor = false;
    body->CreateFixture(&spriteShapeDef);
}



void Player::jump(){
	if(groundObjectsTouching > 0){
		
		b2Vec2 currentVelocity = body->GetLinearVelocity();
		if(currentVelocity.y < 0){
			currentVelocity.y = 0;
		}
		body->SetLinearVelocity(currentVelocity);

		b2Vec2 force = b2Vec2(0.f, 12.0);
		b2Vec2 point = body->GetPosition();

		body->ApplyLinearImpulse(force, point);

		if(!isDead()){
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/jump.wav");
		}
	}
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

bool Player::isDead(){
	return !sprite->isVisible();
}

void Player::update(float dt){
	GameObject::update(dt);

	b2Vec2 currentVelocity = body->GetLinearVelocity();

	if(currentVelocity.y <= 0){
		body->ApplyForceToCenter(b2Vec2(0.0f, -20.f));
	}else{
		body->ApplyForceToCenter(b2Vec2(0.0f, -9.8f));
	}

}

bool Player::spikeIntercect(GameObject* other){
	Rock* rock = (Rock*)other;
	CCPoint location = rock->getPosition();
	location.y -= 30;
	CCPoint center = this->getPosition();

    return (ccpDistance(center, location) < 15);
}
