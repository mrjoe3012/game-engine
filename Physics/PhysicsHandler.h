#pragma once
#include <Matrix.h>
#include "PhysicsObject.h"
#include "CollisionInfo.h"
#include <vector>
#include "QueryResult.h"

using std::vector;

namespace Engine
{

	namespace Physics
	{
		// Handles interactions between physics objects.
		static class PhysicsHandler
		{

		private:
			
			// List of all existing physics objects.
			static vector<PhysicsObject*> objects;

			// Performs a callback operation to call collision delegates after all collisions have been resolved.
			static void CallbackCollisionEvents();

			// Updates each object individually.
			static void UpdateObjects(float dt);
			// Checks for collisions between objects.
			static void HandleCollisions(float dt);
			// Handles collisions between two objects.
			static void HandleKinematicCollision(PhysicsObject& o1, PhysicsObject& o2, float dt);

			static void HandleNonKinematicCollision(PhysicsObject& o1, PhysicsObject& o2, float dt);

			static Vector2D CorrectCollision(PhysicsObject& o1, PhysicsObject& o2, float dt); // Returns last point of intersection.

			static Vector2D CalculateNormalPlane(PhysicsObject& o1, PhysicsObject& o2, Vector2D pointOfContact);

			static float CalculateMomentOfInertia(PhysicsObject& o);
		public:
			static void Initialize();

			// stores information about collision occurences.
			static std::map<PhysicsObject*, CollisionInfo> collisionCallbacks;

			static void RegisterPhysicsObject(PhysicsObject* object);
			static void UnregisterPhysicsObject(PhysicsObject* object);
			// Performs a complete physics step.
			static void PhysicsStep(float dt);
			static float timeScale;

			static vector<PhysicsObject*> GetPhysicsObjects();

			static int layerCount;
			static Engine::Maths::Matrix<bool> layerMatrix;

			static vector<QueryResult> LineCast(Vector2D origin, Vector2D direction, float maxDistance = INFINITY, vector<bool> layers = vector<bool>(layerCount, true), int maxHits = -1);
			static vector<QueryResult> BoxCast(Vector2D origin, float width, float height,  vector<bool> layers = vector<bool>(layerCount, true), int maxHits = -1);
			static vector<QueryResult> BoxCast(Rect rect,  vector<bool> layers = vector<bool>(layerCount, true), int maxHits = -1);
			static vector<QueryResult> CircleCast(Vector2D origin, float radius,  vector<bool> layers = vector<bool>(layerCount, true), int maxHits = -1);
			static vector<QueryResult> CircleCast(Circle circle, vector<bool> layers = vector<bool>(layerCount, true), int maxHits = -1);
		};

	}

}