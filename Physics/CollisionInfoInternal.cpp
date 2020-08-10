#include "CollisionInfoInternal.h"

using Engine::Physics::CollisionInfoInternal;
using namespace Engine::Maths;

CollisionInfoInternal::CollisionInfoInternal(IntersectionInfo inf, bool contained, bool complete)
	:
	intersects(inf),
	containedOverlap(contained),
	pathOverlap(complete)
{

}

CollisionInfoInternal::~CollisionInfoInternal()
{

}

bool CollisionInfoInternal::IsCollision()
{
	// Property that checks if there is a collision.
	return (containedOverlap || pathOverlap || intersects.identical || intersects.pointCount > 0);
}
