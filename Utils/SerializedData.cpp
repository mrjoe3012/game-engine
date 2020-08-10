#include "SerializedData.h"

using Engine::Serialization::SerializedData;
using std::string;

SerializedData::SerializedData()
	:
	SerializedData("","")
{

}

SerializedData::SerializedData(string name, string value)
	:
	name(name),
	value(value)
{

}

SerializedData::~SerializedData()
{

}