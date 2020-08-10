#pragma once

#include <Physics.h>
#include "IClickable.h"
#include "GameScript.h"

namespace Engine
{
	// A wrapper for the physics engine's collider class.
	class Collider
	{
	protected:
		Physics::Collider* collider;
	public:
		Collider();
		virtual ~Collider();

		Physics::Collider* GetCollider();

	};

}