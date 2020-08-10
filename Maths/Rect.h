#pragma once
#include "Primitive.h"
#include "Line.h"

using Engine::Maths::Primitive;
using Engine::Maths::Line;

namespace Engine
{
	namespace Maths
	{

		class Rect : public Primitive // A rectangle.
		{
		public:
			Rect(Vector2D center, float width, float height);
			Rect(Vector2D center, float width, float height, float rotation);
			Rect();
			~Rect();

			bool Contains(Vector2D point) const override;
			std::string ToString() const override;

			float width, height; // Width and height of the shape. Right side = center + width/2 etc.

			Line Top(); // Get the sides of the rectangle, applies rotation to base shape before returning.
			Line Right();
			Line Bottom();
			Line Left();
			Line** GetLines(); // Returns all sides top->right->bottom->left. Pointer is not managed and must be destroyed.
		};

	}
}
