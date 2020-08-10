#pragma once
#include <windows.h>

namespace Engine
{
	namespace Internal
	{

		class HPTimer
		{

		private:
			// The last call to udpate, the call before that and the counter when the timer was reset/created.
			long long int previousUpdate, latestUpdate, startTime;
			// Returns the current counter
			long long int GetCounter();
			// Stored frequency.
			long long int frequency;

		public:
			// Returns frequency.
			long long int GetFrequency();

			HPTimer();
			~HPTimer();
			// Returns time since reset in seconds.
			float GetTime();
			// Returns time since update in seconds.
			double GetDeltaTime();
			// Returns time since update in clock ticks.
			long int GetDeltaCounter();
			// Updates the timer.
			void Update();
			// Resets the timer.
			void Reset();

		};

	}
}