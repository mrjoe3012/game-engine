#pragma once

namespace Engine
{
	class Actor;
	// Base class for all components.
	class Component
	{
	protected:
		// Pointer to the actor this component belongs to.
		Actor* actor;
	public:
		Component(Actor* actor);
		virtual ~Component();

		// Is the component enabled?
		bool enabled;

		// Called every frame
		virtual void Update() = 0;

		Actor& GetActor();
	};

}