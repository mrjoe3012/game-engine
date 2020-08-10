#include "Colour.h"

using Engine::Colour;

Colour Colour::red = Colour(1, 0, 0, 1), Colour::green = Colour(0, 1, 0, 1), Colour::black = Colour(0, 0, 0, 1), Colour::blue = Colour(0, 0, 1, 1), Colour::yellow = Colour(1, 1, 0, 1), Colour::orange = Colour(1, 0.5f, 0, 1), Colour::white = Colour(1, 1, 1, 1), Colour::purple = Colour(0.5f, 0, 0.5f, 1), Colour::pink = Colour(1,0.8f,0.8f,1), Colour::grey = Colour(0.5f,0.5f,0.5f,1), Colour::brown = Colour(0.5f, 0.25f, 0, 1);

Colour::Colour(float r, float g, float b, float a)
	:
	r(r),
	g(g),
	b(b),
	a(a)
{

}

Colour::Colour()
	:
	Colour(1,1,1,1)
{

}

Colour::~Colour()
{

}