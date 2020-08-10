#pragma once
#include <string>
#include <chrono>
#include "IStringConvertable.h"

using std::string;
using std::array;
using std::ostream;
using namespace std::chrono;

namespace Engine
{
	namespace Utils
	{
		// Holds information about the execution of an algorithm
		struct AlgorithmProfileInfo : public IStringConvertable
		{

		private:
			time_point<steady_clock> start, end; // When the algorithm began/stopped
			milliseconds timePassed; // The run time of the algorithm in ms
			
			string algorithmName;

		public:
			AlgorithmProfileInfo(string name);
			~AlgorithmProfileInfo();


			long long GetDuration();
			string GetName();

			void StartTimer(); // Begins counting towards the total algorithm runtime.
			void PauseTimer(); // Pauses counting, can be resumed again.

			string ToString() const override;

			friend ostream& operator<<(ostream&, const AlgorithmProfileInfo& const);

		};

	}
}