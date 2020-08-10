#include "IDebugDrawable.h"
#include "Graphics.h"

using Engine::Internal::IDebugDrawable;

std::vector<IDebugDrawable*> IDebugDrawable::instances = std::vector<IDebugDrawable*>();

IDebugDrawable::IDebugDrawable()
{
	instances.push_back(this);
}

IDebugDrawable::~IDebugDrawable()
{
	for (size_t i = 0; i < instances.size(); i++)
	{
		if (instances[i] == this)
		{
			instances.erase(instances.begin() + i);
			break;
		}
	}
}

std::vector < IDebugDrawable*> IDebugDrawable::GetInstances()
{
	return instances;
}