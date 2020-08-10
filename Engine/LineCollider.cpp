#include "LineCollider.h"

using Engine::LineCollider;
using Engine::PhysicsObject;
using Engine::Maths::Vector2D;
using Engine::Maths::Line;

LineCollider::LineCollider(PhysicsObject* obj)
{
	collider = new Engine::Physics::LineCollider(obj->GetPhysicsObject(), Engine::Maths::Line());
}

LineCollider::~LineCollider()
{

}

Vector2D LineCollider::GetBegin()
{
	Engine::Physics::LineCollider* col = dynamic_cast<Engine::Physics::LineCollider*>(collider);

	return col->line.begin;
}

Vector2D LineCollider::GetEnd()
{
	Engine::Physics::LineCollider* col = dynamic_cast<Engine::Physics::LineCollider*>(collider);

	return col->line.end;
}

void LineCollider::SetBegin(Vector2D p)
{
	Engine::Physics::LineCollider* col = dynamic_cast<Engine::Physics::LineCollider*>(collider);

	col->line.begin = p;
}

void LineCollider::SetEnd(Vector2D p)
{
	Engine::Physics::LineCollider* col = dynamic_cast<Engine::Physics::LineCollider*>(collider);

	col->line.end = p;
}

Line LineCollider::GetLine()
{
	Engine::Physics::LineCollider* col = dynamic_cast<Engine::Physics::LineCollider*>(collider);
	return col->line;
}