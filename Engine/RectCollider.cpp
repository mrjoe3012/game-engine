#include "RectCollider.h"
#include "PhysicsObject.h"

using Engine::RectCollider;
using Engine::PhysicsObject;
using std::unique_ptr;
using namespace Engine::Maths;

RectCollider::RectCollider(PhysicsObject* owner)
{
	collider = new Physics::RectCollider(owner->GetPhysicsObject(), Rect());
}
RectCollider::~RectCollider()
{

}

void RectCollider::SetCenter(Vector2D center)
{
	collider->SetCenter(center);
}

void RectCollider::SetWidth(float width)
{
	static_cast<Physics::RectCollider*>(collider)->rect.width = width;
}

void RectCollider::SetHeight(float height)
{
	static_cast<Physics::RectCollider*>(collider)->rect.height = height;
}

void RectCollider::SetRect(Rect r)
{
	static_cast<Physics::RectCollider*>(collider)->rect = r;
}

Rect RectCollider::GetRect()
{
	return static_cast<Physics::RectCollider*>(collider)->rect;
}

void RectCollider::DrawDebug(Engine::Internal::Graphics* gfx)
{
	ID2D1SolidColorBrush* brush = NULL;

	ID2D1HwndRenderTarget* target = gfx->GetRenderTarget();

	target->CreateSolidColorBrush(D2D1::ColorF(0, 1, 0, 1), &brush);

	Rect r = static_cast<Engine::Physics::RectCollider*>(collider)->rect;

	Line* lines = *r.GetLines();

	for (size_t i = 0; i < 4; i++)
	{
		target->DrawLine(D2D1::Point2F(lines[i].begin.x, -lines[i].begin.y), D2D1::Point2F(lines[i].end.x, -lines[i].end.y), ((ID2D1Brush*)brush));
	}

	brush->Release();
	delete[] lines;
}

unique_ptr<Primitive> RectCollider::GetWorldShape()
{
	Engine::Physics::RectCollider* col = static_cast<Engine::Physics::RectCollider*>(this->collider);
	return unique_ptr<Primitive>(new Rect(collider->GetOwner()->GetPosition(), col->rect.width, col->rect.height));
}