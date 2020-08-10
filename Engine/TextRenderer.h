#pragma once
#include "Renderer.h"
#include <string>
#include "Colour.h"

namespace Engine
{
	class TextRenderer : public Renderer
	{
	public:
		TextRenderer(Actor* a);
		~TextRenderer();

		void Render(Internal::Graphics* gfx);
		void Update() override {}

		std::wstring fontFamily = L"Verdana";
		std::wstring text = L"";
		Colour textColour = Colour(0,0,0,1);
		float fontSize = 50.0f;
	};

}