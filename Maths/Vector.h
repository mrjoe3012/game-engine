#pragma once

namespace Engine
{
	namespace Maths
	{
		// Base class for vectors, just in case we add a vector3 or vector4 in the future.
		class Vector
		{

		public:

			Vector() {};
			~Vector() {};
			// Magnitude properties
			virtual float Magnitude() const = 0;
			virtual float SquareMagnitude() const = 0;

		};
	}
}