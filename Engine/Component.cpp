#include "Component.h"
#include "Actor.h"

using Engine::Component;
using Engine::Actor;

Component::Component(Actor* actor)
	:
	actor(actor),
	enabled(true)
{

}

Component::~Component()
{

}

Actor& Component::GetActor()
{
	return *actor;
}