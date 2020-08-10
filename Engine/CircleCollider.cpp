#include "CircleCollider.h"
#include "PhysicsObject.h"
#include "Graphics.h"

using Engine::Maths::Circle;
using Engine::CircleCollider;
using Engine::PhysicsObject;
using std::unique_ptr;

CircleCollider::CircleCollider(PhysicsObject* obj)
{
	collider = new Engine::Physics::CircleCollider(obj->GetPhysicsObject(), Vector2D(), 10);
}

CircleCollider::~CircleCollider()
{

}

void CircleCollider::SetCenter(Vector2D center)
{
	static_cast<Engine::Physics::CircleCollider*>(collider)->circle.center = center;
}

void CircleCollider::SetRadius(float radius)
{
	static_cast<Engine::Physics::CircleCollider*>(collider)->circle.radius = radius;
}

void CircleCollider::SetCircle(Circle circle)
{
	static_cast<Engine::Physics::CircleCollider*>(collider)->circle = circle;
}

Circle CircleCollider::GetCircle()
{
	return static_cast<Engine::Physics::CircleCollider*>(collider)->circle;
}

void CircleCollider::DrawDebug(Engine::Internal::Graphics* gfx)
{

	Circle c = GetCircle();

	ID2D1HwndRenderTarget* target = gfx->GetRenderTarget();

	ID2D1SolidColorBrush* brush = NULL;
	target->CreateSolidColorBrush(D2D1::ColorF(0, 1, 0, 1), &brush);

	target->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(c.center.x, -c.center.y), c.radius, c.radius), brush);

	brush->Release();
}

std::unique_ptr<Primitive> CircleCollider::GetWorldShape()
{
	return unique_ptr<Primitive>(new Circle(collider->GetOwner()->GetPosition(), static_cast<Engine::Physics::CircleCollider*>(this->collider)->circle.radius));
}