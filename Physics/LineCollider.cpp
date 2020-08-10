#include "LineCollider.h"

using namespace Engine::Physics;

LineCollider::LineCollider(PhysicsObject* owner, Vector2D begin, Vector2D end)
	:
	LineCollider(owner, Line(begin, end))
{

}
LineCollider::LineCollider(PhysicsObject* owner, Line l)
	:
	Collider(owner),
	line(l)
{

}
LineCollider::~LineCollider()
{

}

Vector2D LineCollider::GetCenter()
{
	// Returns the center point of the line
	return line.MidPoint();
}
void LineCollider::SetCenter(Vector2D center)
{
	// Shifts begin and end points by the distance from current center
	// to new center.
	Vector2D movementVector = GetCenter() - center;

	line.begin += movementVector;
	line.end += movementVector;

}

float LineCollider::GetRotation()
{
	// Takes the inverse tangent of the gradient as m = tan(0); where 0 = theta
	float gradient = line.Gradient();
	// if the gradient is undefined, the angle to the y-axis is 0.
	if (isnan(gradient) || isinf(gradient))
		return 0;
	// The angle returned is from the x-axis.
	return 90.0f - (float)atan(gradient);

}
void LineCollider::SetRotation(float rot)
{
	line = Line::RotateLine(line, rot);
}