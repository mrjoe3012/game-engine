#include "HPTimer.h"

using Engine::Internal::HPTimer;

HPTimer::HPTimer()
	:
	frequency(GetFrequency()),
	startTime(GetCounter())
{
	latestUpdate = startTime, previousUpdate = startTime;
}

HPTimer::~HPTimer()
{

}

long long int HPTimer::GetCounter()
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return counter.QuadPart;
}

long long int HPTimer::GetFrequency()
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return freq.QuadPart;
}

void HPTimer::Reset()
{
	startTime = GetCounter();
}

float HPTimer::GetTime()
{
	float time = (((float)(GetCounter() - startTime)) / ((float)frequency));
	return time;
}

double HPTimer::GetDeltaTime()
{
	double dt = (((double)latestUpdate-(double)previousUpdate)/(double)frequency);
	return dt;
}

void HPTimer::Update()
{
	previousUpdate = latestUpdate;
	latestUpdate = GetCounter();
}

long int HPTimer::GetDeltaCounter()
{
	return latestUpdate - previousUpdate;
}

