#include "Actor.h"

using Engine::Actor;
using namespace Engine::Maths;

std::vector<Actor*> Actor::actorList = std::vector<Actor*>();

Actor::Actor(string name, string tag)
	:
	name(name),
	tag(tag),
	componentList()
{
	actorList.push_back(this);
}

Actor::Actor(string name)
	:
	Actor(name, "")
{

}

Actor::~Actor()
{
	for (size_t i = 0; i < actorList.size(); i++)
	{
		if (actorList[i] == this)
		{
			actorList.erase(actorList.begin() + i);
			break;
		}
	}

	for (size_t i = 0; i < componentList.size(); i++)
	{
		delete componentList[i];
	}

}

void Actor::_update()
{
	// Update each component
	for (Component* c : componentList)
	{
		if(c->enabled)
			c->Update();
	}
}

void Actor::Update()
{
	// Update each actor instance
	for (Actor* a : actorList)
	{
		a-> _update();
	}
}

std::vector<Actor*> Actor::GetActorList()
{
	return actorList;
}

std::vector<Actor*> Actor::FindActorsByName(std::string name)
{
	std::vector<Actor*> result;

	for (auto a : actorList)
	{
		if (a->name == name)
			result.push_back(a);
	}

	return result;
}

Actor* Actor::FindActorByName(std::string name)
{
	Actor* result = nullptr;

	for (auto a : actorList)
	{
		if (a->name == name)
		{
			result = a;
			break;
		}
	}
	return result;
}

std::vector<Actor*> Actor::FindActorsByTag(std::string tag)
{
	std::vector<Actor*> result;

	for (auto a : actorList)
	{
		if (a->tag == tag)
			result.push_back(a);
	}

	return result;
}
Actor* Actor::FindActorByTag(std::string tag)
{
	Actor* result = nullptr;

	for (auto a : actorList)
	{
		if (a->tag == tag)
		{
			result = a;
			break;
		}
	}
	return result;
}