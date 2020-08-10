#pragma once
#include <string>
#include <iostream>
using std::ostream;

namespace Engine
{
	namespace Utils
	{
		// For any class that can be represented as a string, inspired by c#'s object.ToString()
		// Abstract and should not be instantiated (interface behaviour)
		class IStringConvertable
		{
		public:
			IStringConvertable();
			~IStringConvertable();

			virtual std::string ToString() const = 0;
		};
	}
}