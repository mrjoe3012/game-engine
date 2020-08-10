#pragma once
#include "CollisionInfoInternal.h"
#include "PhysicsObject.h"

namespace Engine
{

	namespace Physics
	{
		// Used to handle collision checking between colliders.
		static class CollisionHandler
		{

		private:
			// Checking for path overlaps -> An object may have velocity of such a high magnitude
			// that in one physics step it goes through and object and there are no points of intersection.
			// To check for this case we check for intersections between the paths of the objects.
			// Note this is flawed it should check against the shapes as well.
			static bool CheckForPathOverlap(PhysicsObject& obj1, PhysicsObject& obj2, float dt);
			// Checks if the shape's center is contained within the object -> no points of intersection but collision.
			static bool CheckForContainedOverlap(PhysicsObject& obj1, PhysicsObject& obj2);

		public:
			// Checks for all cases of collision and returns the collision info in a structure.
			static CollisionInfoInternal CheckCollision(PhysicsObject& obj1, PhysicsObject& obj2, float dt);
			

		};

	}

}