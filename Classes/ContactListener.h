#pragma once

#include "cocos2d.h"
using namespace cocos2d;

#include "Box2D/Box2D.h"
#include <vector>
#include "GameObject.h"


struct ContactData {
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    bool operator==(const ContactData& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

class CContactListener : public b2ContactListener {

public:
    std::vector<ContactData>_contacts;
    
    CContactListener();
    ~CContactListener();
    
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);    
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
};
