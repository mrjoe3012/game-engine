#include "CollisionInfo.h"
#include "PhysicsObject.h"

using Engine::Physics::CollisionInfo;
using Engine::Physics::PhysicsObject;

CollisionInfo::CollisionInfo(PhysicsObject* other)
	:
	other(other)
{

}

CollisionInfo::~CollisionInfo()
{

}

PhysicsObject* CollisionInfo::GetOther()
{
	return other;
}