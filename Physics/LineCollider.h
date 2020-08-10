#pragma once
#include "Collider.h"

namespace Engine
{
	namespace Physics
	{
		// An edge collider
		class LineCollider : public Collider
		{
		public:
			LineCollider(PhysicsObject* owner, Vector2D begin, Vector2D end);
			LineCollider(PhysicsObject* owner, Line l);
			~LineCollider();

			// The line shape of the collider.
			Line line;

			Vector2D GetCenter() override;
			void SetCenter(Vector2D) override;

			float GetRotation() override;
			void SetRotation(float) override;
		};
	}
}