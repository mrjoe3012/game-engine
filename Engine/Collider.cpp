#include "Collider.h"

using Engine::Collider;

Collider::Collider()
	:
	collider(nullptr)
{

}

Collider::~Collider()
{
}

Engine::Physics::Collider* Collider::GetCollider()
{
	return collider;
}