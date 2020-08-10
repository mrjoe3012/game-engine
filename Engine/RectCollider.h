#pragma once
#include "Collider.h"
#include "IDebugDrawable.h"
#include "Graphics.h"
#include <Maths.h>

using namespace Engine::Maths;

namespace Engine
{
	class PhysicsObject;
	// Encapsulates the rect collider from the physics engine.
	// OnClick should be Delegate<typename>
	class RectCollider : public Collider, public Engine::Internal::IDebugDrawable, public Engine::Internal::IClickable
	{
	public:
		RectCollider(PhysicsObject* owner);
		~RectCollider();

		void SetWidth(float width);
		void SetHeight(float height);
		void SetCenter(Vector2D center);
		void SetRect(Rect rect);
		Rect GetRect();

		void DrawDebug(Engine::Internal::Graphics* gfx) override;

		std::unique_ptr<Primitive> GetWorldShape() override;
	};
}