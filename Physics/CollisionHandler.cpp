#include "CollisionHandler.h"
#include "RectCollider.h"
#include "CollisionInfoInternal.h"
#include "CircleCollider.h"
#include "LineCollider.h"

using namespace Engine::Physics;
using namespace Engine::Maths;

CollisionInfoInternal CollisionHandler::CheckCollision(PhysicsObject& obj1, PhysicsObject& obj2, float dt)
{
	IntersectionInfo info;
	bool pathOverlap = false;
	bool contOverlap = false;

	Collider* col1 = obj1.GetCollider();
	Collider* col2 = obj2.GetCollider();

	if (!(col1 && col2))
	{
		throw std::runtime_error("Cannot check collisions if one or more physics objects do not have colliders.");
	}

	// Try to find the derived types of the colliders.
	RectCollider* rCol1 = dynamic_cast<RectCollider*>(col1);
	RectCollider* rCol2 = dynamic_cast<RectCollider*>(col2);

	CircleCollider* cCol1 = dynamic_cast<CircleCollider*>(col1);
	CircleCollider* cCol2 = dynamic_cast<CircleCollider*>(col2);

	LineCollider* lCol1 = dynamic_cast<LineCollider*>(col1);
	LineCollider* lCol2 = dynamic_cast<LineCollider*>(col2);
	// Check each individual case for collider types.
	if (rCol1 && rCol2) // Rect on rect collision
	{
		info = CheckIntersection(rCol1->rect, rCol2->rect);
	}
	else if (rCol1 && lCol2)
	{
		info = CheckIntersection(rCol1->rect, lCol2->line);
	}
	else if (lCol1 && rCol2)
	{
		info = CheckIntersection(rCol2->rect, lCol1->line);
	}
	else if ((rCol1 && cCol2) )
	{
		info = CheckIntersection(rCol1->rect, cCol2->circle);
	}
	else if ((cCol1 && rCol2))
	{
		info = CheckIntersection(rCol2->rect, cCol1->circle);
	}
	else if (cCol1 && cCol2)
	{
		info = CheckIntersection(cCol1->circle, cCol2->circle);
	}
	else if (cCol1 && lCol2)
	{
		info = CheckIntersection(lCol2->line, cCol1->circle);
	}
	else if (lCol1 && cCol2)
	{
		info = CheckIntersection(lCol1->line, cCol2->circle);
	}
	else if (lCol1 && lCol2)
	{
		info = CheckIntersection(lCol1->line, lCol2->line);
	}

	// If there are no points of intersection, check for special collision cases.
	if (info.pointCount == 0)
	{
		contOverlap = CheckForContainedOverlap(obj1, obj2);
		pathOverlap = CheckForPathOverlap(obj1, obj2, dt);
	}

	return CollisionInfoInternal(info, contOverlap, pathOverlap);

}

bool CollisionHandler::CheckForContainedOverlap(PhysicsObject& o1, PhysicsObject& o2)
{
	
	Collider* col1 = o1.GetCollider();
	Collider* col2 = o2.GetCollider();

	RectCollider* rCol1 = dynamic_cast<RectCollider*>(col1);
	RectCollider* rCol2 = dynamic_cast<RectCollider*>(col2);

	CircleCollider* cCol1 = dynamic_cast<CircleCollider*>(col1);
	CircleCollider* cCol2 = dynamic_cast<CircleCollider*>(col2);

	LineCollider* lCol1 = dynamic_cast<LineCollider*>(col1);
	LineCollider* lCol2 = dynamic_cast<LineCollider*>(col2);

	if (rCol1 && rCol2)
	{
		return (rCol1->rect.Contains(rCol2->GetCenter()) || rCol2->rect.Contains(rCol1->GetCenter()));
	}
	else if ((rCol1 && cCol2))
	{
		return (rCol1->rect.Contains(cCol2->GetCenter()) || cCol2->circle.Contains(rCol1->GetCenter()));
	}
	else if ((cCol1 && rCol2))
	{
		return (rCol2->rect.Contains(cCol1->GetCenter()) || cCol1->circle.Contains(rCol2->GetCenter()));
	}
	else if (rCol1 && lCol2)
	{
		return (rCol1->rect.Contains(lCol2->GetCenter()));
	}
	else if (lCol1 && rCol2)
	{
		return (rCol2->rect.Contains(lCol1->GetCenter()));
	}
	else if (cCol1 && cCol2)
	{
		return (cCol1->circle.Contains(cCol2->GetCenter()) || cCol2->circle.Contains(cCol1->GetCenter()));
	}
	else if (cCol1 && lCol2)
	{
		return (cCol1->circle.Contains(lCol2->GetCenter()));
	}
	else if (lCol1 && cCol2)
	{
		return (cCol2->circle.Contains(lCol1->GetCenter()));
	}
	else if (lCol1 && lCol2)
	{
		return false;
	}

	throw std::runtime_error("Unexpected error occured while checking for a contained overlap.");
	return false;
}

bool CollisionHandler::CheckForPathOverlap(PhysicsObject& o1, PhysicsObject& o2, float dt)
{
	Vector2D o1Begin, o2Begin;
	Line o1Path, o2Path;

	o1Begin = o1.GetPosition() - (o1.translationalVelocity*dt);
	o2Begin = o2.GetPosition() - (o2.translationalVelocity*dt);

	o1Path = Line(o1Begin, o1.GetPosition());
	o2Path = Line(o2Begin, o2.GetPosition());

	auto info = CheckIntersection(o1Path, o2Path);

	return info.pointCount > 0 || info.identical;

}