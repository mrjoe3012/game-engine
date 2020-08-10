#pragma once
#include <Maths.h>

namespace Engine
{
	namespace Physics
	{
		class PhysicsObject;
		struct QueryResult
		{
		public:
			QueryResult();
			QueryResult(PhysicsObject*);
			~QueryResult();

			PhysicsObject* hit = nullptr;

		};
	}
}