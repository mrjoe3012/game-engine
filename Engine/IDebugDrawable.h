#pragma once
#include <vector>

namespace Engine
{
	namespace Internal
	{
		class Graphics;
		// Used for objects that can be drawn in debug mode. Objects such as colliders that have a shape that can't normally be seen.
		class IDebugDrawable
		{
		private:
			static std::vector<IDebugDrawable*> instances;
		public:
			IDebugDrawable();
			~IDebugDrawable();

			bool drawDebug;

			virtual void DrawDebug(Graphics*) = 0;

			static std::vector<IDebugDrawable*> GetInstances();

		};
	}
}