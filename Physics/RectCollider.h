#pragma once
#include "Collider.h"
#include "PhysicsObject.h"
#include <Maths.h>

using namespace Engine::Maths;

namespace Engine
{
	namespace Physics
	{
		// A collider of rectangular shape.
		class RectCollider : public Collider
		{
		public:
			RectCollider(PhysicsObject* owner, Vector2D center, float width, float height, float rotation);
			RectCollider(PhysicsObject* owner, Rect r);
			~RectCollider();
			
			// The rectangle shape of the collider, can be changed at any time.
			Rect rect;
			
			Vector2D GetCenter() override;
			void SetCenter(Vector2D) override;

			float GetRotation() override;
			void SetRotation(float) override;

		};

	}
}