#include "ISerializable.h"

using Engine::Serialization::ISerializable;
using std::string;

ISerializable::ISerializable(std::string identifier)
	:
	identifier(identifier)
{

}

ISerializable::~ISerializable()
{

}