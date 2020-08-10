#pragma once
#include "Renderer.h"
#include <Maths.h>
#include "Graphics.h"
#include "Colour.h"

namespace Engine
{
	// Renders a rectangle on the screen.
	class RectRenderer : public Renderer
	{
	public:
		RectRenderer(Actor* actor);
		RectRenderer(Actor* actor, float width, float height);
		~RectRenderer();

		Colour colour;

		float width;
		float height;

		void Render(Internal::Graphics* gfx) override;

		void Update() override;

	};

}