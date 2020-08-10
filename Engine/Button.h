#pragma once

#include "IClickable.h"
#include "Component.h"
#include <Maths.h>

using std::unique_ptr;

namespace Engine
{

	class Button : public Component, public Internal::IClickable
	{
	public:
		Button(Actor* a);
		~Button();

		float width = 100, height = 100;

		void Update() override {}

		unique_ptr<Primitive> GetWorldShape() override;
	};

}