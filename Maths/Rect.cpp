#define USE_VECTOR_DEFINES

#include "Rect.h"
#include <string>

using Engine::Maths::Rect;
using std::to_string;

Rect::Rect(Vector2D center, float width, float height)
	:
	Primitive(center, 0),
	width(width),
	height(height)
{

}

Rect::Rect(Vector2D center, float width, float height, float rotation)
	:
	Primitive(center, rotation),
	width(width),
	height(height)
{

}

Rect::Rect()
	:
	Primitive(),
	width(0),
	height(0)

{

}

Rect::~Rect()
{

}

bool Rect::Contains(Vector2D point) const // Returns true if the rectangle contains the point.
{
	
	Vector2D rotatedPoint = Vector2D::AddRotation(center, point, -rotation);
	
	float boundXLow = (center.x - (width / 2.0f)), boundXHigh = (center.x + (width / 2.0f));
	float boundYLow = (center.y - (height / 2.0f)), boundYHigh = (center.y + (height / 2.0f));

	return (rotatedPoint.x >= boundXLow && rotatedPoint.x <= boundXHigh) && (rotatedPoint.y >= boundYLow && rotatedPoint.y <= boundYHigh);

}

std::string Rect::ToString() const
{
	std::string str("Rect { center: " + this->center.ToString() + " width: " + to_string(this->width) + " height: " + to_string(this->height) + " }");
	return str;
}


/*
*	The following return the sides of the rectangle by getting the ordinary sides and applying the shape's rotation to the line.
*/

Line Rect::Top()
{
	Vector2D begin(center.x - (width / 2.0f), center.y + (height / 2.0f));
	Vector2D end(center.x + (width / 2.0f), center.y + (height / 2.0f));

	Line top(begin, end);

	top.begin = Vector2D::AddRotation(center, begin, rotation);
	top.end = Vector2D::AddRotation(center, end, rotation);

	return top;
}

Line Rect::Right()
{
	Vector2D begin(center.x + (width / 2.0f), center.y - (height / 2.0f));
	Vector2D end(center.x + (width / 2.0f), center.y + (height / 2.0f));

	Line Right(begin, end);

	Right.begin = Vector2D::AddRotation(center, Right.begin, rotation);
	Right.end = Vector2D::AddRotation(center, Right.end, rotation);

	return Right;
}

Line Rect::Bottom()
{
	Vector2D begin(center.x - (width / 2.0f), center.y - (height / 2.0f));
	Vector2D end(center.x + (width / 2.0f), center.y - (height / 2.0f));

	Line Bottom(begin, end);

	Bottom.begin = Vector2D::AddRotation(center, Bottom.begin, rotation);
	Bottom.end = Vector2D::AddRotation(center, Bottom.end, rotation);

	return Bottom;
}

Line Rect::Left()
{
	Vector2D begin(center.x - (width / 2.0f), center.y - (height / 2.0f));
	Vector2D end(center.x - (width / 2.0f), center.y + (height / 2.0f));

	Line Left(begin, end);

	Left.begin = Vector2D::AddRotation(center, Left.begin, rotation);
	Left.end = Vector2D::AddRotation(center, Left.end, rotation);

	return Left;
}
#pragma optimize("", off)
Line** Rect::GetLines() // This pointer is not managed! Destroy it yourself. This returns each of the lines making up this shape.
{
	Line* lines = new Line[4]
	{
		Top(),
		Right(),
		Bottom(),
		Left()
	};

	return &lines;
}
