#include "RectCollider.h"

using Engine::Physics::RectCollider;
using Engine::Physics::CollisionInfo;
using Engine::Physics::PhysicsObject;
using namespace Engine::Maths;

RectCollider::RectCollider(PhysicsObject* owner, Vector2D center, float width, float height, float rotation)
	:
	RectCollider(owner, Rect(center, width, height, rotation))
{

}

RectCollider::RectCollider(PhysicsObject* owner, Rect r)
	:
	Collider(owner),
	rect(r)
{

}

RectCollider::~RectCollider()
{

}

float RectCollider::GetRotation()
{
	return rect.rotation;
}

void RectCollider::SetRotation(float rot)
{
	rect.rotation = rot;
}

Vector2D RectCollider::GetCenter()
{
	return rect.center;
}

void RectCollider::SetCenter(Vector2D c)
{
	rect.center = c;
}