#pragma once
#include "Renderer.h"
#include "Colour.h"
#include <Maths.h>

namespace Engine
{
	// Renders an ellipse onto the screen
	class EllipseRenderer : public Renderer
	{
	public:
		EllipseRenderer(Actor* actor);
		EllipseRenderer(Actor* actor, float radiusX, float radiusY);
		~EllipseRenderer();

		// Radii of the ellipse
		float radiusX;
		float radiusY;

		// Colour to render
		Colour colour;

		void Update() override {}
		void Render(Internal::Graphics* gfc) override;

	};

}