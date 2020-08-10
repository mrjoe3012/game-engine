#include "Transform.h"

using Engine::Transform;
using namespace Engine::Maths;

Transform::Transform(Vector2D pos, float rot)
	:
	position(pos),
	rotation(rot)
{

}

Transform::Transform()
	:
	Transform(Vector2D(), float())
{

}

Transform::~Transform()
{

}