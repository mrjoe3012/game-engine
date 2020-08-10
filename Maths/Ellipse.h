#pragma once
#include "Primitive.h"
#include "Vector2D.h"

using Engine::Maths::Primitive;
using Engine::Maths::Vector2D;

namespace Engine
{
	namespace Maths
	{
		class Ellipse : public Primitive // Represents an ellipse
		{

		public:
			Ellipse(Vector2D center, Vector2D radii);
			Ellipse();
			~Ellipse();

			Vector2D radii; // Vector holds 2 radii for x and y.

			bool Contains(Vector2D) const override;

			int GetX(int y, int** results) const; // Returns the amount of values satisfying the equation, populates results with an array containing the values. At most two.
			int GetY(int x, int** results) const; // These functions ignore rotations and simply use the general ellipse equation: ((x-h)^2/a^2)+((y-h)^2/b^2) = 1 where a is the x- radius and b is the y-radius and (h,k) is the center

			std::string ToString() const override;
		};
	}
}