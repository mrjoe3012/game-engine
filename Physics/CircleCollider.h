#pragma once
#include "Collider.h"

namespace Engine
{
	namespace Physics
	{
		// Collider with a circular boundary.
		class CircleCollider : public Collider
		{
		public:

			CircleCollider(PhysicsObject* owner, Vector2D center, float radius);
			CircleCollider(PhysicsObject* owner, Circle c);
			~CircleCollider();

			// The circle shape, can be modified at any time.
			Circle circle;

			Vector2D GetCenter() override;
			void SetCenter(Vector2D) override;

			float GetRotation() override;
			void SetRotation(float) override;
		};
	}
}