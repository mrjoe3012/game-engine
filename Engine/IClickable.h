#pragma once
#include <Maths.h>
#include <Delegate.h>
#include <vector>
#include <memory>

namespace Engine
{
	namespace Internal
	{
		class IClickable
		{
		private:
			static std::vector<IClickable*> instanceList;
		public:
			IClickable();
			virtual ~IClickable();

			virtual std::unique_ptr<Primitive> GetWorldShape() = 0;
			// Delegate<typename, KeyCode> where KeyCode is the mouse button that was used to click.
			Engine::Events::GenericDelegate* OnClick = nullptr;

			static std::vector<IClickable*> GetInstances() { return instanceList; }
		};
	}
}