#pragma once
#include <string>

namespace Engine
{

	namespace Serialization
	{
		// Represents a member variable that has been serialzied.
		struct SerializedData
		{
		public:
			SerializedData();
			SerializedData(std::string, std::string);
			~SerializedData();

			std::string name, value;

		};

	}

}