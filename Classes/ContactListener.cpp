#include "ContactListener.h"

CContactListener::CContactListener()//: _contacts() 
{
}

CContactListener::~CContactListener() 
{
}

void CContactListener::BeginContact(b2Contact* contact) 
{
	
	GameObject *spriteA = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject *spriteB = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	// let objects decide what sould happen
	if(spriteA && spriteB){
		spriteA->resolveCollision(spriteB);
		spriteB->resolveCollision(spriteA);
	}
}

void CContactListener::EndContact(b2Contact* contact) 
{
	GameObject *spriteA = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject *spriteB = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	// let objects decide what sould happen
	if(spriteA && spriteB){
		spriteA->resolveEndCollision(spriteB);
		spriteB->resolveEndCollision(spriteA);
	}
}

void CContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) 
{
}

void CContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) 
{
}
