#pragma once
#include "Component.h"
#include <vector>
#include <Maths.h>

using Engine::Maths::Vector2D;

namespace Engine
{
	namespace Internal
	{
		class Graphics;
	}
	// A base class for all renderer components.
	class Renderer : public  Component
	{
	private:
	public:
		Renderer(Actor* a);
		virtual ~Renderer();
		// Higher priority is rendered in front.
		int priority;
		// All renderers are scalable.
		Vector2D scale;

		virtual void Render(Internal::Graphics* graphics) = 0;

	};

}