#pragma once


namespace Engine
{
	namespace Physics
	{
		class PhysicsObject;

		// Structure passed to colliders on collisions.
		struct CollisionInfo
		{
		private:
			PhysicsObject* other;

		public:
			CollisionInfo(PhysicsObject* other);
			~CollisionInfo();
			PhysicsObject* GetOther();

		};

	}
}