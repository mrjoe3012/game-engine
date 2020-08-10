#include "Ellipse.h"
#include <Debug.h>

using Engine::Maths::Ellipse;
using Engine::Maths::Vector2D;
using Engine::Utils::AlgorithmProfileInfo;
using Engine::Utils::AlgorithmProfiler;
using std::to_string;

Ellipse::Ellipse(Vector2D center, Vector2D radii)
	:
	Primitive(center, 0),
	radii(radii)
{

}

Ellipse::Ellipse()
	:
	Primitive(),
	radii()
{

}

Ellipse::~Ellipse()
{

}

std::string Ellipse::ToString() const
{
	return std::string("Ellipse { center: " + center.ToString() + " radii: " + radii.ToString() + " }");
}

int Ellipse::GetX(int y, int** xValues) const // Rotation ignored, returns the corresponding xValues with passed y value.
{


	*xValues = nullptr; // Init data
	int valueCount = 0;

	int eqtnSquared = ((pow((int)radii.x, 2))*(1 - (pow(y - (int)center.y, 2) / pow((int)radii.y, 2)))); // The value of the equation squared before adding the constant.
																										 // used to check the roots of the equation, (real, equal), (real, distinct), (unreal)

	if (eqtnSquared == 0) // The roots are equal and so there is only one value.
	{
		*xValues = new int[1];
		(*xValues)[0] = 0 + (int)center.x;
		valueCount = 1;
	}
	else if(eqtnSquared > 0) // The roots are real and distinct and so there are two values
	{
		*xValues = new int[2];
		valueCount = 2;

		(*xValues)[0] = sqrt(eqtnSquared) + (int)center.x;
		(*xValues)[1] = (-sqrt(eqtnSquared)) + (int)center.x;
	}
	else // The roots are unreal and there are no values
	{
		valueCount = 0;
	}


	return valueCount;
}


int Ellipse::GetY(int x, int** yValues) const // Rotation ignored, returns the corresponding yValues with passed x value.
{
	*yValues = nullptr;
	int valueCount = 0;

	int eqtnSquared = (pow((int)radii.y, 2)) * (1 - (pow(x - (int)center.x, 2) / pow((int)radii.x, 2)));

	if (eqtnSquared == 0)
	{
		*yValues = new int[1];
		(*yValues)[0] = 0 + (int)center.y;
		valueCount = 1;
	}
	else if (eqtnSquared > 0)
	{
		*yValues = new int[2];
		valueCount = 2;

		(*yValues)[0] = sqrt(eqtnSquared) + (int)center.y;
		(*yValues)[1] = (-sqrt(eqtnSquared)) + (int)center.y;
	}
	else
	{
		valueCount = 0;
	}

	return valueCount;
}

bool Ellipse::Contains(Vector2D point) const
{
	
	point = Vector2D::AddRotation(center, point, -rotation);

	int* xValues = nullptr; // The boundaries of the ellipse calculated at the point's location
	int* yValues = nullptr;
	int xValueCount, yValueCount;

	xValueCount = Ellipse::GetX(point.y, &xValues);
	yValueCount = Ellipse::GetY(point.x, &yValues);
	if (xValueCount == 0 || yValueCount == 0) // Point cannot be in the ellipse as no boundaries are in either direction.
		return false;
	else if (xValueCount + yValueCount == 4) // Point lies inside of the ellipse as boundaries exist on all sides of the point.
		return true;
	else if (xValueCount == 2 || yValueCount == 2 && !(xValueCount == 2 && yValueCount == 2)) // Point must be inside of ellipse as at least one value exists for 
		return true;																		  // both x and y and either x or y has two one value meaning the point lies on the ellipse.
	else
		return false;

}