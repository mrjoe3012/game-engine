#pragma once
#include "Collider.h"
#include "PhysicsObject.h"

namespace Engine
{
	// Encapsulates the line collider from the physics engine
	class LineCollider : public Collider
	{
	public:
		LineCollider(PhysicsObject* obj);
		~LineCollider();

		void SetBegin(Maths::Vector2D);
		void SetEnd(Maths::Vector2D);

		Maths::Vector2D GetBegin();
		Maths::Vector2D GetEnd();

		Maths::Line GetLine();
	};

}