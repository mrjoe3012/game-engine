#include "AlgorithmProfiler.h"

using namespace Engine::Utils;
using std::ostream;

AlgorithmProfiler* AlgorithmProfiler::instance = nullptr;

AlgorithmProfiler::AlgorithmProfiler()
	:
	profileLogs()
{
	if (!instance)
		instance = this;
}

AlgorithmProfiler::~AlgorithmProfiler()
{
	if (instance)
		delete instance;

	for (AlgorithmProfileInfo* i : profileLogs)
	{
		if(i)
			delete i;
	}

	profileLogs.clear();
	instance = nullptr;
}

AlgorithmProfiler* AlgorithmProfiler::GetInstance()
{
	if (!instance)
		new AlgorithmProfiler();

	AlgorithmProfiler* inst = instance;

	return inst;
}

std::vector<AlgorithmProfileInfo> AlgorithmProfiler::GetProfiles()
{
	std::vector<AlgorithmProfileInfo> profiles; // Create a copy

	for (AlgorithmProfileInfo* i : profileLogs)
	{
		profiles.push_back(*i);
	}

	return profiles;
}

AlgorithmProfileInfo& AlgorithmProfiler::CreateProfile(std::string name)
{
	AlgorithmProfileInfo* profileInfo = new AlgorithmProfileInfo(name);
	profileLogs.push_back(profileInfo); // Registers the profile with this class.

	return *profileInfo;
}

