#include "PhysicsObject.h"
#include "Collider.h"
#include "Actor.h"

using Engine::PhysicsObject;
using Engine::Collider;
using Engine::Actor;

std::map<Engine::Physics::PhysicsObject*, Actor*> PhysicsObject::objectActors = std::map<Engine::Physics::PhysicsObject*, Actor*>();

PhysicsObject::PhysicsObject(Actor* owner)
	:
	Component(owner),
	collider(nullptr),
	obj(owner->transform.position, owner->transform.rotation)
{
	objectActors[&obj] = owner;
}
PhysicsObject::~PhysicsObject()
{
	if (collider)
		delete collider;

	objectActors.erase(&obj);
}

void PhysicsObject::SetCollider(Collider* c)
{
	collider = c;
	obj.SetCollider(c->GetCollider());
}
Collider* PhysicsObject::GetCollider()
{
	return collider;
}

void PhysicsObject::Update()
{
	actor->transform.position = obj.GetPosition();
	actor->transform.rotation = obj.GetRotation();
}

Engine::Physics::PhysicsObject* PhysicsObject::GetPhysicsObject()
{
	return &obj;
}

Actor* PhysicsObject::GetActorFromPhysicsObject(Engine::Physics::PhysicsObject* obj)
{
	Actor* res = nullptr;
	try
	{
		res = objectActors.at(obj);
	}
	catch (std::out_of_range& const e)
	{
		res = nullptr;
	}

	return res;
}