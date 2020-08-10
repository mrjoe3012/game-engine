#include "AlgorithmProfileInfo.h"

using Engine::Utils::AlgorithmProfileInfo;
using std::string;
using std::to_string;

AlgorithmProfileInfo::AlgorithmProfileInfo(string name)
	:
	algorithmName(name),
	timePassed()
{
}

AlgorithmProfileInfo::~AlgorithmProfileInfo()
{

}

string AlgorithmProfileInfo::GetName()
{
	return this->algorithmName;
}

long long AlgorithmProfileInfo::GetDuration()
{
	return this->timePassed.count();
}

void AlgorithmProfileInfo::StartTimer()
{
	this->start = high_resolution_clock::now();
}

void AlgorithmProfileInfo::PauseTimer()
{
	this->end = high_resolution_clock::now();
	// Add time passed so that the clock can be paused and reset multiple times.
	this->timePassed += duration_cast<milliseconds>(end - start);
}

string AlgorithmProfileInfo::ToString() const
{
	return string("AlgorithmProfileInfo { name: " + algorithmName + " duration: " + to_string(this->timePassed.count()) + " }");
}

ostream& Engine::Utils::operator<<(ostream& o, const AlgorithmProfileInfo& const a)
{
	o << a.ToString();
	return o;
}


