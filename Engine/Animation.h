#pragma once
#include "Component.h"
#include <vector>
#include "AnimationSet.h"

namespace Engine
{
	class SpriteRenderer;
	// Component that takes control of the spriterender's sprite to play an animation.
	class Animation : public Component
	{
	private:
		// Internal timing
		long long unsigned int counter;
		long long unsigned int previousCounter;
		// Reference to the actor's renderer.
		SpriteRenderer* renderer;
	public:
		Animation(Actor* a);
		~Animation();
		// The animation sets to be used.
		std::vector<AnimationSet*> animations;
		// The animation set to use.
		int animationIndex;

		void Update() override;
	};

}