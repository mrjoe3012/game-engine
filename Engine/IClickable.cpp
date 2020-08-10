#include "IClickable.h"

using Engine::Internal::IClickable;
using std::vector;

vector<IClickable*> IClickable::instanceList = std::vector<IClickable*>();

IClickable::IClickable()
{
	instanceList.push_back(this);
}

IClickable::~IClickable()
{
	for (size_t i = 0; i < instanceList.size(); i++)
	{
		if (instanceList[i] == this)
		{
			instanceList.erase(instanceList.begin() + i);
			break;
		}
	}
}