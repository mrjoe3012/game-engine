#pragma once
#include "Collider.h"
#include "IDebugDrawable.h"

namespace Engine
{
	class PhysicsObject;
	// Encapsulates the physics engine's circle collider.
	// OnClick should be Delegate<typename>
	class CircleCollider : public Collider, public Internal::IDebugDrawable, public Internal::IClickable
	{
	public:
		CircleCollider(PhysicsObject* owner);
		~CircleCollider();

		void SetCenter(Vector2D);
		void SetRadius(float);
		void SetCircle(Circle c);
		Circle GetCircle();

		void DrawDebug(Engine::Internal::Graphics* gfx) override;

		std::unique_ptr<Primitive> GetWorldShape() override;
	};
}