#define USE_VECTOR_DEFINES
#include "PhysicsObject.h"
#include "PhysicsHandler.h"
#include "Collider.h"

using namespace Engine::Maths;
using Engine::Physics::PhysicsObject;
using Engine::Physics::Collider;

PhysicsObject::PhysicsObject()
	: PhysicsObject(VECTOR2D_ZERO, 0.0f)
{

}

PhysicsObject::PhysicsObject(Vector2D center)
	:
	PhysicsObject(center, 0.0f)
{

}

PhysicsObject::PhysicsObject(Vector2D center, float rotation)
	:
	PhysicsObject(center, rotation, nullptr)
{
}

PhysicsObject::PhysicsObject(Vector2D center, float rotation, Collider* c)
	:
	position(center),
	rotation(rotation),
	collider(c)
{
	PhysicsHandler::RegisterPhysicsObject(this); // When created, register self with the physics handler.
}

PhysicsObject::~PhysicsObject()
{
	PhysicsHandler::UnregisterPhysicsObject(this); // When destroyed, unregister self with the physics handler.

	if (collider)
		delete collider;
	// Delete collision callback
	// Only objects that still exist have their collision delegate called.
	auto it = PhysicsHandler::collisionCallbacks.find(this);
	if (it != PhysicsHandler::collisionCallbacks.end())
		PhysicsHandler::collisionCallbacks.erase(it);
}

void PhysicsObject::SetCollider(Collider* c)
{
	if (collider)
		delete collider;

	collider = c;

}

Collider* PhysicsObject::GetCollider()
{
	return collider;
}

void PhysicsObject::Update(float dt)
{
	positionLastUpdate = this->position;

	this->position += (this->translationalVelocity*dt);
	this->rotation += (this->rotationalVelocity*dt);

	if (rotation > 360)
	{
		rotation = (int)rotation % 360;
	}
	else if (rotation < -360)
	{
		rotation = -(abs((int)rotation) % 360);
	}

	UpdateCollider();
}

void PhysicsObject::ReverseUpdate(float dt)
{
	// Multiply velocities by negative delta time to undo changes.
	this->position += (this->translationalVelocity*-dt);
	this->rotation += (this->rotationalVelocity*-dt);
	UpdateCollider();
}

void PhysicsObject::UpdateCollider()
{
	if(collider)
	{
		collider->SetCenter(this->position);
		collider->SetRotation(this->rotation);
	}
}

Vector2D PhysicsObject::GetRealTransaltionalVelocity()
{
	return position - positionLastUpdate;
}

unsigned int PhysicsObject::GetCollisionLayer()
{
	return collisionLayer;
}

void PhysicsObject::SetCollisionLayer(unsigned int index)
{
	if (index >= PhysicsHandler::layerCount)
		throw std::out_of_range("Layer index out of range.");
	else
		collisionLayer = index;
}