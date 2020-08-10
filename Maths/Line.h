#pragma once
#include "Vector2D.h"
#include <iostream>

using Engine::Maths::Vector2D;
using std::ostream;

namespace Engine
{
	namespace Maths
	{
		// Represents a line from point begin to end
		struct Line : public IStringConvertable
		{
		public:

			Vector2D begin; // start point
			Vector2D end; // end point

			Line(Vector2D b, Vector2D e);
			Line();
			~Line();

			Vector2D LineVector() const; // Returns the line as a vector (end-begin)
			Vector2D MidPoint() const; // Returns the midpoint of the line.

			float Gradient() const;
			float ConstantOffset() const;

			float GetX(float y) const;
			float GetY(float x) const;

			static Line RotateLine(Line line, float angle); // Rotates the line by the angle provided using begin as pivot.
			static Line RotateLine(Line line, Vector2D pivot, float angle); // Rotates line around the pivot.
			static Line AddRotation(Line line, Vector2D pivot,  float rotation); // Rotates the line by its rotation + passed rotation.

			std::string ToString() const override;

			friend ostream& operator<<(ostream&, const Line& const rhs);
			bool operator==(Line& rhs) const; 
		};

	}
}