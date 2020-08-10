#pragma once
#include <Sprite.h>
#include <vector>

using Engine::Assets::Sprite;

namespace Engine
{
	// An animation set represents one animation. It holds a
	// collection of sprites and the length of the animation.
	// The Animation component will the use an animation set to animate a sprite renderer.
	class AnimationSet
	{
	public:
		AnimationSet(std::vector<Sprite*>);
		AnimationSet(AnimationSet&);
		AnimationSet();
		~AnimationSet();

		float length;
		std::vector<Sprite*> sprites;
	};

}