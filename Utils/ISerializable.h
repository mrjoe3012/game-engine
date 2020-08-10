#pragma once
#include <string>
#include "SerializedObject.h"

namespace Engine
{

	namespace Serialization
	{
		// An object that can have its state serialized.
		// The object can implement its deserialization 
		// seperately and is not required by the interface.
		class ISerializable
		{
		private:
			std::string identifier;
		public:
			ISerializable(std::string identifier);
			virtual ~ISerializable();
			std::string GetIdentifier() { return identifier; }
			virtual SerializedObject Serialize() = 0;
		};

	}

}