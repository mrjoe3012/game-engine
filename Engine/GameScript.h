#pragma once
#include "Component.h"

namespace Engine
{
	// A component used to add custom logic scripts to actors.
	class GameScript : public Component
	{
	public:
		//virtual void OnLoad() = 0;
		//virtual void OnUnload() = 0;
		GameScript(Actor* a)
			:
			Component(a)
		{

		}
		virtual ~GameScript() {}
		virtual void Update() override {}
	};
}