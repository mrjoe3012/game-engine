#pragma once
#include "Renderer.h"
#include <Sprite.h>

namespace Engine
{
	// Renders a bitmap onto the screen.
	class SpriteRenderer : public Renderer
	{
	private:
		Assets::Sprite* sprite;
	public:
		SpriteRenderer(Actor* actor);
		~SpriteRenderer();

		void SetSprite(Assets::Sprite* sprite);
		Assets::Sprite* GetSprite();

		void Render(Internal::Graphics* gfx) override;
		void Update() override;

	};

}