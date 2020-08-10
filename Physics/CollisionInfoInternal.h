#pragma once
#include <Maths.h>

using namespace Engine::Maths;

namespace Engine
{

	namespace Physics
	{

		struct CollisionInfoInternal
		{

		public:
			CollisionInfoInternal(IntersectionInfo intersects, bool containedOverlap, bool completeOverlap);
			~CollisionInfoInternal();
			// Points of intersection
			IntersectionInfo intersects;
			// Are the centers contained within each other?
			bool containedOverlap;
			bool pathOverlap;
			bool IsCollision();

		};

	}

}