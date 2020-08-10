#pragma once
#include "Component.h"
#include "Transform.h"
#include <Physics.h>
#include <map>

namespace Engine
{
	class Collider;
	class Actor;
	// Encapsulates a physics object through a component.
	class PhysicsObject : public Component
	{
	private:
		Physics::PhysicsObject obj;
		Collider* collider;

		static std::map<Engine::Physics::PhysicsObject*, Actor*> objectActors;

	public:
		PhysicsObject(Actor*);
		~PhysicsObject();

		void SetCollider(Collider* c);
		Collider* GetCollider();

		void Update() override;
		// Returns the Physics::PhysicsObject.
		Physics::PhysicsObject* GetPhysicsObject();

		static Actor* GetActorFromPhysicsObject(Engine::Physics::PhysicsObject* obj);
	};
}