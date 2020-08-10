#include "Line.h"

using Engine::Maths::Line;
using Engine::Maths::Vector2D;
using std::to_string;

Line::Line()
	:
	begin(),
	end()
{

}

Line::Line(Vector2D begin, Vector2D end)
	:
	begin(begin),
	end(end)
{

}

Line::~Line()
{

}

Line Line::RotateLine(Line line, float angle) // Rotates with the begin point as the origin
{
	Vector2D newEnd = Vector2D::RotatePoint(line.begin, line.end, angle); // Rotate the original end point

	return Line(line.begin, newEnd);

}

Line Line::RotateLine(Line line, Vector2D pivot, float angle) // Rotates the line using the passed pivot.
{
	line.begin = Vector2D::RotatePoint(pivot, line.begin, angle+180.0f); // Rotate the begin point, add 180 deg to the angle to represent the opposite side of the line.
	line.end = Vector2D::RotatePoint(pivot, line.end, angle); // Rotate the end point

	return line;
}

Line Line::AddRotation(Line line, Vector2D pivot, float rotation) // Sets rotation to rotation + passed rotation
{
	Line rotatedLine; 

	rotatedLine.begin = Vector2D::AddRotation(pivot, line.begin, rotation); // Add rotation to both points
	rotatedLine.end = Vector2D::AddRotation(pivot, line.end, rotation);

	return rotatedLine;
}

Vector2D Line::LineVector() const // Returns the
{
	return end - begin; // Vector form AB-> = B - A
}

Vector2D Line::MidPoint() const // Midpt formula: midpt = (a+b)/2
{
	Vector2D mid = begin + end; 
	mid.x /= 2.0f; 
	mid.y /= 2.0f;

	return mid;

}

float Line::Gradient() const
{
	if (abs(end.x - begin.x) <= 0.001f)
		return NAN;

	float gradient =  (end.y - begin.y) / (end.x - begin.x);

	if (gradient < 0.001 && gradient > -0.001)
	{
		return 0;
	}
	else
		return gradient;

}

float Line::ConstantOffset() const
{
	float y = begin.x*Gradient();
	return begin.y - y;
}

float Line::GetX(float y) const
{
	if (isnan(Gradient()))
		return this->begin.x;
	else
		return (y - this->ConstantOffset()) / this->Gradient();
}

float Line::GetY(float x) const
{
	if (isnan(Gradient()))
		return NAN;
	else
		return (Gradient()*x) + ConstantOffset();
}

std::string Line::ToString() const
{
	return std::string("Line { begin: " + begin.ToString() + " end: " + end.ToString() + " magnitude: " + to_string(LineVector().Magnitude()) + "}");
}


ostream& Engine::Maths::operator<<(ostream& os, const Line& const rhs)
{
	os << rhs.ToString();
	return os;
}

bool Line::operator==(Line& rhs) const
{
	return (begin == rhs.begin) && (end == rhs.end);
}
