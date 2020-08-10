#pragma once
#include "IStringConvertable.h"
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include "AlgorithmProfileInfo.h"

using std::vector;
using std::array;
using std::ostream;
using std::string;

namespace Engine
{
	namespace Utils
	{
		// Utility singleton class for measuring algorithm performance.
		class AlgorithmProfiler
		{
			
		private:
			AlgorithmProfiler();

			static AlgorithmProfiler* instance;

			vector<AlgorithmProfileInfo*> profileLogs; // A history of every algorithm profile throughout the program's execution.

		public:
			~AlgorithmProfiler();


			AlgorithmProfileInfo& CreateProfile(string); // Used to create a profile and add it to the list, creating a profile normally will not do this.
			vector<AlgorithmProfileInfo> GetProfiles(); // ^^ consider changing to allow using constructor
			static  AlgorithmProfiler*  GetInstance();

		};

	}
}