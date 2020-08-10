#define USE_VECTOR_DEFINES
#include "Vector2D.h"
#include "Line.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <Debug.h>

using Engine::Maths::Vector2D;
using Engine::Maths::Line;
using Engine::Utils::AlgorithmProfiler;
using Engine::Utils::AlgorithmProfileInfo;
using std::to_string;

Vector2D::Vector2D()
	: 
	Vector2D(0.0f,0.0f)
{

}

Vector2D::Vector2D(float x, float y)
	:
	x(x),
	y(y)
{

}

Vector2D::~Vector2D()
{

}

std::string Vector2D::ToString() const
{
	std::string str("Vector2D { x: " + to_string(this->x) + " y: " + to_string(this->y) + " }");
	return str;
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
	Vector2D result = *this;
	result.x += rhs.x;
	result.y += rhs.y;
	return result;
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
	Vector2D result = *this;
	result.x -= rhs.x;
	result.y -= rhs.y;
	return result;
}

Vector2D Vector2D::operator*(float rhs) const
{
	Vector2D v = *this;
	v.x *= rhs;
	v.y *= rhs;
	
	return v;
}

Vector2D Vector2D::operator/(float rhs) const
{
	Vector2D v = *this;

	v.x /= rhs;
	v.y /= rhs;

	return v;
}

void Vector2D::operator*=(float rhs)
{
	*this = (*this * rhs);
}

void Vector2D::operator/=(float rhs)
{
	*this = (*this / rhs);
}

void Vector2D::operator+=(const Vector2D& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
}

Vector2D Engine::Maths::operator*(float lhs, const Vector2D& rhs)
{
	return rhs * lhs;
}

bool Vector2D::operator==(const Vector2D& rhs) const
{
	return ((rhs.x >= this->x - 0.01 && rhs.x <= this->x + 0.01) && (rhs.y >= this->y - 0.01 && rhs.y <= this->y + 0.01));
}

bool Vector2D::operator!=(const Vector2D& rhs) const
{
	return !(*this == rhs);
}

// Friend function for ostream operator.
std::ostream& Engine::Maths::operator<<(std::ostream& os, const Vector2D& const rhs)
{
	os << rhs.ToString();
	return os;
}

float Vector2D::Magnitude() const
{
	// Root of square magnitude.
	return sqrt(SquareMagnitude());
}

float Vector2D::SquareMagnitude() const
{
	// Square magnitude using components -> |v|^2 = x^2 + y^2 / a^2 = b^2 + c^2
	return powf(x, 2.0f) + powf(y, 2.0f);
}

Vector2D Vector2D::RotatePoint(Vector2D pivot, Vector2D point, float angle)
{
	Vector2D newPoint; // This is a journey from pivot to new point

	Vector2D vectorJourney = (point - pivot);
	float magnitude = vectorJourney.Magnitude(); // Get the distance from the origin, this will be 
												 // used for the radius of a circle with center (pivot.x,pivot.y)

	double angleRadians = M_PI / (180.0 / angle);

	double x = (magnitude*sinf(angleRadians)); // Parametric equation of a circle / trig 
	double y = (magnitude*cosf(angleRadians));
	
	newPoint.x = x; // Minor data loss
	newPoint.y = y;
	return newPoint + pivot; // Add pivot to get the point instead of a journey from pivot!
}

Vector2D Vector2D::AddRotation(Vector2D pivot, Vector2D point, float rotation) // Adds passed rotation to current rotation around pivot point
{

	float currentRot = Vector2D::Angle((point - pivot), DIRECTION_UP); // Get the angle between point to pivot and y-axis

	if (point.x < pivot.x) currentRot = 360 - currentRot; // If the point is behind the y-axis, use the longest angle.

	return Vector2D::RotatePoint(pivot, point, currentRot + rotation);

}

float Vector2D::Angle(Vector2D a, Vector2D b) // Returns the shortest angle between a and b
{
	float dotProduct = Vector2D::ScalarProduct(a, b);
	float angleRadians = acosf(dotProduct / (a.Magnitude()*b.Magnitude())); // cosx = (a.b)/(|a|*|b|)
	if (isnan(angleRadians)) angleRadians = 0;

	return (angleRadians * 180) / M_PI;
}

float Vector2D::ScalarProduct(Vector2D a, Vector2D b) // Returns a.b
{
	return (a.x*b.x) + (a.y*b.y);
}

Vector2D Vector2D::Normalize(Vector2D v) // Normalizes vector: v(normalized) = (1/|v|)*v
{
	if(v.Magnitude() != 0)
		return (1.0f/v.Magnitude()) * v;
	else
	{
		return v;
	}
}
