#include "Animation.h"
#include "Actor.h"
#include "EngineManager.h"

using Engine::Internal::EngineManager;
using Engine::Animation;
using Engine::Assets::Sprite;
using Engine::Actor;

Animation::Animation(Actor* a)
	:
	Component(a),
	animationIndex(0),
	animations(),
	counter(0)
{
	renderer = actor->GetComponent<SpriteRenderer>();
}

Animation::~Animation()
{
	for (size_t i = 0; i < animations.size(); i++)
	{
		delete animations[i];
	}
}

void Animation::Update()
{
	// Store a pointer to the desired animation set.
	auto animSet = animations[animationIndex];
	// Store the length of the animation in seconds.
	float length = animSet->length;

	// Store the counter's value
	previousCounter = counter;

	// Store the frequency of the Engine's high precision timer.
	auto frequency = EngineManager::timer.GetFrequency();
	// Store the delta time in ticks.
	unsigned long long int elapsedTicks = EngineManager::timer.GetDeltaCounter();

	// Update the counter.
	counter += elapsedTicks;

	// Find the total amount of ticks in one animation cycle.
	unsigned long long int totalTicks = length * frequency;
	// Find the amount of ticks between each animation frame: the keyframes.
	unsigned long long int increment = totalTicks / animSet->sprites.size();
	// Figure out what tick value the next frame will change at.
	unsigned long long int nextStep = (previousCounter - (previousCounter%increment)) + increment;
	// If the next step is longer than the animation, set it to the end of the animaiton.
	if (nextStep > totalTicks)
		nextStep -= (nextStep - totalTicks);
	// If we have gone past the point for the next step, change sprite.
	if (counter >= nextStep)
	{
		// Get the index.
		int index = (nextStep / increment)-1;
		// Copy the sprite.
		renderer->SetSprite(new Sprite(*animSet->sprites[index]));
		// Reset counter if we have reached the final frame.
		if (nextStep == totalTicks)
		{
			counter = 0;
		}

	}
}

