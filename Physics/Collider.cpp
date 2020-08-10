#define USE_VECTOR_DEFINES
#include "PhysicsObject.h"
#include "Collider.h"

using namespace Engine::Maths;
using Engine::Physics::Collider;
using Engine::Physics::PhysicsObject;
using Engine::Physics::CollisionInfo;

Collider::Collider(PhysicsObject* owner)
	:
	owner(owner),
	delegateEvent(nullptr)
{

}


Collider::~Collider()
{
	// Assumes ownership of the delegate event.
	if (delegateEvent)
		delete delegateEvent;
}

PhysicsObject* Collider::GetOwner()
{
	return owner;
}

void Collider::OnCollision(CollisionInfo info)
{
	// Defaults by invoking the delegate event.
	if (delegateEvent)
		delegateEvent->Invoke1P((void*)&info);
}