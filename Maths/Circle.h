#pragma once
#include "Ellipse.h"

using Engine::Maths::Ellipse;
using Engine::Maths::Primitive;

namespace Engine
{
	namespace Maths
	{
		class Circle : public Primitive // Represents a circle with equation r^2 = (x-h)^2 - (y-k)^2
		{

		public:
			Circle(Vector2D center, float radius);
			Circle();
			~Circle();

			float radius; 

			Ellipse GetEllipse() const; // Returns an ellipse with equal radii

			std::string ToString() const override;
			bool Contains(Vector2D point) const override;
			
			bool operator==(const Circle& const rhs) const;
		};
	}
}
