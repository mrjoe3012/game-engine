#pragma once
#include <Maths.h>
#include <map>

using namespace Engine::Maths;

namespace Engine
{
	namespace Physics
	{

		class Collider;

		class PhysicsObject
		{
		private:
			// Physics objects can have colliders
			Collider* collider;
			// Updates the position of the collider.
			void UpdateCollider();
			

			Vector2D position;
			float rotation;

			Vector2D positionLastUpdate;
			
			unsigned int collisionLayer = 0;

		public:
			PhysicsObject();
			PhysicsObject(Vector2D center);
			PhysicsObject(Vector2D center, float rotation);
			PhysicsObject(Vector2D center, float rotation, Collider* collider);
			~PhysicsObject();

			// Linear velocity, pixels per second.
			Vector2D translationalVelocity;
			// Rotational velocity, degrees per second.
			float rotationalVelocity;

			Vector2D GetRealTransaltionalVelocity();

			Vector2D GetPosition() { return position; UpdateCollider(); }
			void SetPosition(Vector2D p) { position = p; UpdateCollider(); }
			float GetRotation() { return rotation; UpdateCollider(); }
			void SetRotation(float r) { rotation = r; UpdateCollider(); }
			// Update the object.
			void Update(float dt);
			// Reverse the effects of the last update.
			void ReverseUpdate(float dt);

			void SetCollider(Collider* collider);
			Collider* GetCollider();
			// used for culling simulation.
			bool enabled = true;
			// used for collision handling types
			//bool kinematic = true;

			// used for solving non-kinematic collisions.
			//float mass = 1;

			void SetCollisionLayer(unsigned int index);
			unsigned int GetCollisionLayer();
		};

	}
}