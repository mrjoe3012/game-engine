#pragma once
#include <IStringConvertable.h>
#include <iostream>
#include "Vector2D.h"
#include "IntersectionInfo.h"

using Engine::Maths::Vector2D;
using Engine::Utils::IStringConvertable;


namespace Engine
{
	namespace Maths
	{

		// Represents a primitive shape
		// String conversions possible
		class Primitive : public IStringConvertable 
		{
		public:
			Primitive(Vector2D center, float rotation);
			Primitive(Vector2D center) : Primitive(center, 0.0f) {}
			Primitive();
			virtual ~Primitive();

			friend std::ostream& operator<<(std::ostream& os, const Primitive& const rect);

			Vector2D center; // The center of the primitive shape.
			float rotation; // The rotation of the object relative to the positive y axis. 0 meaning that the positive y-axis of the shape is equal to the positive y-axis.
			virtual bool Contains(Vector2D point) const = 0; // A function that returns true if the point is inside of the shape or touching it.
		};
	}
}