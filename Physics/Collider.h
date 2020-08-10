#pragma once

#include <Maths.h>
#include "CollisionInfo.h"
#include <Delegate.h>

using namespace Engine::Maths;
using Engine::Events::Delegate;
using Engine::Events::GenericDelegate;

namespace Engine
{
	namespace Physics
	{

		class PhysicsObject;

		// Abstract base class that outlines base functions for all collider types.
		class Collider
		{

		private:
			// The physics object that this collider belongs to.
			PhysicsObject* owner;
		public:
			
			Collider(PhysicsObject* owner);
			virtual ~Collider();

			// Different collider types have different ways of setting centers, using virtual accessors to allow abstraction.
			virtual void SetCenter(Vector2D) = 0;
			virtual Vector2D GetCenter() = 0;

			virtual void SetRotation(float) = 0;
			virtual float GetRotation() = 0;

			PhysicsObject* GetOwner();

			bool staticObject = false;

			// OnCollision event, can be overriden in custom colliders.
			virtual void OnCollision(CollisionInfo info);

			// Can this object pass through solid colliders? Useful for triggers etc.
			bool permeable;
			// Generic delegate for event handling without overriding a collider.
			// Can be a delegate invoked on any type, but will always return void and take 1 parameter of type CollisionInfo
			// Example: delegateEvent = static_cast<GenericDelegate*>(new Delegate<InstanceType, CollisionInfo>(&instance));
			// *(collider.delegateEvent) = &InstanceType::SomeFunction;
			GenericDelegate* delegateEvent;

		};

	}
}

