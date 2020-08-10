#include "QueryResult.h"
#include "PhysicsObject.h"

using Engine::Physics::QueryResult;
using Engine::Physics::PhysicsObject;
using namespace Engine::Maths;

QueryResult::QueryResult()
{

}

QueryResult::QueryResult(PhysicsObject* obj)
	:
	hit(obj)
{

}

QueryResult::~QueryResult()
{

}