#pragma once

namespace Engine
{
	// Represents and RGBA colour.
	struct Colour
	{
	public:
		Colour(float, float, float, float);
		Colour();
		~Colour();
		float r, g, b, a;

		static Colour red, green, black, blue, yellow, orange, white, purple, pink, grey, brown;
	};

}