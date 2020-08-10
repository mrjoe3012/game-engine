#pragma once
#include <Maths.h>

namespace Engine
{
	// Stores a position in space and a rotation. Rotations are angles in a clockwise direction from the y-axis.
	struct Transform
	{
	public:
		Transform(Maths::Vector2D pos, float rot);
		Transform();
		~Transform();

		Maths::Vector2D position;
		float rotation;
	};

}