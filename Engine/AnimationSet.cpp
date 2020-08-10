#include "AnimationSet.h"

using Engine::AnimationSet;

AnimationSet::AnimationSet()
	:
	AnimationSet(std::vector<Sprite*>())
{

}

AnimationSet::AnimationSet(std::vector<Sprite*> sprites)
	:
	sprites(sprites),
	length(1.0f)
{

}

AnimationSet::AnimationSet(AnimationSet& set)
	:
	AnimationSet()
{
	this->length = set.length;

	for (size_t i = 0; i < set.sprites.size(); i++)
	{
		sprites[i] = new Sprite(*set.sprites[i]);
	}

}

AnimationSet::~AnimationSet()
{
	for (size_t i = 0; i < sprites.size(); i++)
	{
		delete sprites[i];
	}
}