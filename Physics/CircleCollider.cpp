#include "CircleCollider.h"

using namespace Engine::Physics;
using namespace Engine::Maths;

CircleCollider::CircleCollider(PhysicsObject* owner, Vector2D center, float radius)
	:
	CircleCollider(owner, Circle(center, radius))
{

}

CircleCollider::CircleCollider(PhysicsObject* owner, Circle c)
	:
	Collider(owner),
	circle(c)
{

}

CircleCollider::~CircleCollider()
{

}

Vector2D CircleCollider::GetCenter()
{
	return circle.center;
}

void CircleCollider::SetCenter(Vector2D center)
{
	circle.center = center;
}

float CircleCollider::GetRotation()
{
	return circle.rotation;
}

void CircleCollider::SetRotation(float rotation)
{
	circle.rotation = rotation;
}