#include "Primitive.h"

using Engine::Maths::Primitive;

Primitive::Primitive(Vector2D center, float rotation)
	:
	center(center),
	rotation(rotation)
{

}

Primitive::Primitive()
	:
	center()
{

}

Primitive::~Primitive()
{

}


std::ostream& Engine::Maths::operator<<(std::ostream& os, const Primitive& const rhs) // Return string version of the primitive.
{
	os << rhs.ToString();
	return os;
}
