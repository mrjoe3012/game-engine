#pragma once
#include "SerializedData.h"
#include <vector>

namespace Engine
{
	namespace Serialization
	{
		// Represents an object instance that has been serialized into text format.
		class SerializedObject
		{

		public:
			SerializedObject();
			SerializedObject(std::string);
			~SerializedObject();
			// a unique string identifier for the object type.
			std::string identifier;
			// the data that represents the member variables of the instance.
			std::vector<SerializedData> data;
			// Reads serialized data from a file.
			static std::vector<SerializedObject> ReadSerializedData(std::string filename);
			// Writes serialized data to a file.
			static void WriteSerializedData(std::vector<SerializedObject> data, std::string filename, unsigned int mode);
		};
	}
}