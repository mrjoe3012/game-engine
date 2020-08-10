#define _USE_MATH_DEFINES
#include "PhysicsHandler.h"
#include "CollisionHandler.h"
#include "Collider.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include <math.h>
#include "CollisionInfoInternal.h"

using namespace Engine::Maths;

using Engine::Physics::PhysicsHandler;
using std::vector;
using std::map;
using Engine::Physics::PhysicsObject;
using Engine::Physics::CollisionHandler;
using Engine::Physics::Collider;
using Engine::Physics::CollisionInfoInternal;
using Engine::Physics::CollisionInfo;

vector<PhysicsObject*> PhysicsHandler::objects = vector<PhysicsObject*>();

float PhysicsHandler::timeScale = 1.0f;

map<PhysicsObject*, CollisionInfo> PhysicsHandler::collisionCallbacks = map<PhysicsObject*, CollisionInfo>();

int PhysicsHandler::layerCount = 5;

Matrix<bool> PhysicsHandler::layerMatrix = Matrix<bool>(layerCount);

void PhysicsHandler::RegisterPhysicsObject(PhysicsObject* obj)
{
	objects.push_back(obj);
}

void PhysicsHandler::UnregisterPhysicsObject(PhysicsObject* obj)
{
	int index = -1, i= 0;
	for (PhysicsObject* o : objects)
	{
		if (o == obj)
		{
			index = i;
			break;
		}
		i++;
	}

	if(index != -1)
		objects.erase(objects.begin() + index);

}

void PhysicsHandler::PhysicsStep(float dt)
{
	UpdateObjects(dt*timeScale);
	HandleCollisions(dt*timeScale);
	CallbackCollisionEvents();
}

void PhysicsHandler::UpdateObjects(float dt)
{

	for (PhysicsObject* obj : objects)
	{
		if(obj->enabled)
			obj->Update(dt);
	}

}
// Goes through each collision event and calls the delegate. Done through a callback
// so that objects can be deleted after collisions. The event is processed after collisions have been resolved
// to prevent conflicts.
void PhysicsHandler::CallbackCollisionEvents()
{
	map<PhysicsObject*, CollisionInfo>::iterator it = collisionCallbacks.begin();

	for (; it != collisionCallbacks.end(); it++)
	{
		if (it->first->GetCollider())
			it->first->GetCollider()->OnCollision(it->second);
	}

	collisionCallbacks.clear();

}

void PhysicsHandler::HandleCollisions(float dt)
{
	int index = 0;
	// Check each physics object with each physics object infront of it in the list.
	for (PhysicsObject* pObj : objects)
	{
		for (size_t i = index+1; i < objects.size(); i++)
		{

			PhysicsObject* o1 = pObj;
			PhysicsObject* o2 = objects[i];
			if(o1->enabled&& o2->enabled)
				if (o1->GetCollider() && o2->GetCollider())
				{
					if ((!(o1->GetCollider()->staticObject && o2->GetCollider()->staticObject)) && (layerMatrix[o1->GetCollisionLayer()][o2->GetCollisionLayer()]))
					{
						CollisionInfoInternal colInfo = CollisionHandler::CheckCollision(*o1, *o2, dt);

							if (colInfo.IsCollision())
							{
								/*if (o1->GetCollider()->permeable || o2->GetCollider()->permeable || (o1->kinematic && o2->kinematic))
									HandleKinematicCollision(*o1, *o2, dt);
								else if (!o1->kinematic && !o2->kinematic)
									HandleNonKinematicCollision(*o1, *o2, dt);*/
								HandleKinematicCollision(*o1, *o2, dt);
							}
					}
				}
		}

		index++;
	}

}

Vector2D PhysicsHandler::CorrectCollision(PhysicsObject& o1, PhysicsObject& o2, float dt)
{
	Vector2D pointOfContact = Vector2D();
	// Move back objects just enough;
	for (size_t i = 0; i < 10; i++)
	{

		o1.ReverseUpdate(dt / 10.0f);
		o2.ReverseUpdate(dt / 10.0f);

		CollisionInfoInternal colInfo = CollisionHandler::CheckCollision(o1, o2, dt - ((dt / 10.0f)*(i + 1)));

		if (colInfo.IsCollision())
		{
			if (colInfo.intersects.pointCount > 0)
			{
				if (colInfo.intersects.pointCount == 0) // pointCount > 1
				{
					pointOfContact = colInfo.intersects.pointsOfIntersection[0];
				}
				else
				{
					Vector2D p1 = colInfo.intersects.pointsOfIntersection[0], p2 = colInfo.intersects.pointsOfIntersection[colInfo.intersects.pointCount - 1];
					auto l = Line(p1, p2);
					pointOfContact = l.MidPoint();
				}
			}
			else
			{
				auto l = Line(o1.GetPosition(), o2.GetPosition());
				pointOfContact = l.MidPoint();
			}
		}
	}
	return pointOfContact;
}

void PhysicsHandler::HandleKinematicCollision(PhysicsObject& o1, PhysicsObject& o2, float dt)
{
	if (!(o1.GetCollider()->permeable || o2.GetCollider()->permeable))
	{
		CorrectCollision(o1, o2, dt);

		// Reverse objects slightly more than necessary
		//o1.ReverseUpdate(dt*1.1f);
		//o2.ReverseUpdate(dt*1.1f);

		// Attempt to apply velocity components individually

		Vector2D o1NewPos = o1.GetPosition(), o2NewPos = o2.GetPosition();

		{
			Vector2D position = o1.GetPosition();

			position.x += o1.translationalVelocity.x*dt;

			o1.SetPosition(position);

			auto colInfo = CollisionHandler::CheckCollision(o1, o2, dt);

			if (!colInfo.IsCollision())
			{
				o1NewPos.x = position.x;
			}

			position.x -= o1.translationalVelocity.x*dt;

			o1.SetPosition(position);
		}

		{
			Vector2D position = o2.GetPosition();

			position.x += o2.translationalVelocity.x*dt;

			o2.SetPosition(position);

			CollisionInfoInternal colInfo = CollisionHandler::CheckCollision(o1, o2, dt);

			if (!colInfo.IsCollision())
			{
				o2NewPos.x = position.x;
			}

			position.x -= o2.translationalVelocity.x*dt;

			o2.SetPosition(position);
		}

		{
			Vector2D position = o1.GetPosition();

			position.y += o1.translationalVelocity.y*dt;

			o1.SetPosition(position);

			CollisionInfoInternal colInfo = CollisionHandler::CheckCollision(o1, o2, dt);

			if (!colInfo.IsCollision())
			{
				o1NewPos.y = position.y;
			}

			position.y -= o1.translationalVelocity.y*dt;

			o1.SetPosition(position);
		}

		{
			Vector2D position = o2.GetPosition();

			position.y += o2.translationalVelocity.y*dt;

			o2.SetPosition(position);

			CollisionInfoInternal colInfo = CollisionHandler::CheckCollision(o1, o2, dt);

			if (!colInfo.IsCollision())
			{
				o2NewPos.y = position.y;
			}

			position.y -= o2.translationalVelocity.y*dt;

			o2.SetPosition(position);
		}
		// Update the positions of the objects.
		o1.SetPosition(o1NewPos);
		o2.SetPosition(o2NewPos);
	}

	collisionCallbacks.insert(collisionCallbacks.begin(), std::pair<PhysicsObject*, CollisionInfo>(&o1, CollisionInfo(&o2)));
	collisionCallbacks.insert(collisionCallbacks.begin(), std::pair<PhysicsObject*, CollisionInfo>(&o2, CollisionInfo(&o1)));

	/*o1.GetCollider()->OnCollision(CollisionInfo(&o2));
	o2.GetCollider()->OnCollision(CollisionInfo(&o1));*/

}

void PhysicsHandler::HandleNonKinematicCollision(PhysicsObject& o1, PhysicsObject& o2, float dt)
{
	/*float elasticity = 1.0f;
	float o1w = o1.rotationalVelocity*(M_PI / 180.0f);
	float o2w = o2.rotationalVelocity*(M_PI / 180.0f);
	float l1 = CalculateMomentOfInertia(o1), l2 = CalculateMomentOfInertia(o2);
	Vector2D pointOfContact = Vector2D();

	pointOfContact = CorrectCollision(o1, o2, dt);

	Vector2D normal = CalculateNormalPlane(o1, o2, pointOfContact);

	Vector2D r1 = pointOfContact - o1.GetPosition(), r2 = pointOfContact - o2.GetPosition();
	Vector2D ap1 = o1.translationalVelocity + Vector2D(-o1w*r1.y, o1w*r1.x), bp1 = o2.translationalVelocity + Vector2D(-o2w*r2.y, o2w*r2.x);

	Vector2D ab1 = ap1 - bp1;

	double impulse = (-(1.0f + elasticity)*Vector2D::ScalarProduct(ab1, normal)) / (((1.0f/o1.mass)+(1.0f/o2.mass)) + (powf(Vector2D::ScalarProduct(r1, normal),2.0f)/l1) + (powf(Vector2D::ScalarProduct(r2, normal), 2.0f)/l2));

	Vector2D a2 = o1.translationalVelocity + ((impulse*normal)/o1.mass), b2 = o2.translationalVelocity - ((impulse*normal) / o2.mass);
	float wa2 = o1w + (Vector2D::ScalarProduct(r1, impulse*normal) / l1), wb2 = o2w - (Vector2D::ScalarProduct(r2, impulse*normal) / l2);

	o1.translationalVelocity = a2;
	o1.rotationalVelocity = wa2 * (180.0f/M_PI);

	o2.translationalVelocity = b2;
	o2.rotationalVelocity = wb2 * (180.0f/M_PI);*/
}
// Moment of inertia is scaled by 0.001
float PhysicsHandler::CalculateMomentOfInertia(PhysicsObject& o1)
{
	/*Collider* col = o1.GetCollider();
	RectCollider* r = nullptr;
	CircleCollider* c = nullptr;
	float scale = 1.0f / 10.0f;

	if (col)
	{
		r = dynamic_cast<RectCollider*>(col);
		c = dynamic_cast<CircleCollider*>(col);

		long long int l = 0.0f;

		if (r)
		{
			l = scale*o1.mass*((r->rect.width*powf(r->rect.height, 3))/12);
		}
		else if (c)
		{
			l = scale*o1.mass*((M_PI*powf(c->circle.radius, 4)) / 4);
		}

		return l;

	}
	else
	{
		return 0;
	}*/
	return 0;
}

Vector2D PhysicsHandler::CalculateNormalPlane(PhysicsObject& o1, PhysicsObject& o2, Vector2D pointOfContact)
{
	Collider *col1 = nullptr, *col2 = nullptr;
	CircleCollider *c1 = nullptr, *c2 = nullptr;
	RectCollider *r1 = nullptr, *r2 = nullptr;

	col1 = o1.GetCollider();
	col2 = o2.GetCollider();

	if (col1&&col2)
	{
		Vector2D normal;

		c1 = dynamic_cast<CircleCollider*>(col1);
		c2 = dynamic_cast<CircleCollider*>(col2);

		r1 = dynamic_cast<RectCollider*>(col1);
		r2 = dynamic_cast<RectCollider*>(col2);

		if (c1&&c2)
		{
			Vector2D c1c2 = o1.GetPosition() - o2.GetPosition();
			normal = Vector2D::Normalize(c1c2);
		}
		else if ((c1&&r2) || (r1&&c2))
		{
			auto cCol = c1 ? c1 : c2;

			Vector2D cpt = pointOfContact - cCol->circle.center;

			cpt = Vector2D(-cpt.y, cpt.x);

			normal = Vector2D::Normalize(cpt);
		}
		else if (r1&&r2)
		{
			std::vector<Vector2D>* focus = nullptr;

			Vector2D r1Closest, r2Closest;

			std::vector<Vector2D> r1vtc = std::vector<Vector2D>
			{
				r1->rect.Left().begin,
				r1->rect.Left().end,
				r1->rect.Right().begin,
				r1->rect.Right().end
			};

			std::vector<Vector2D> r2vtc = std::vector<Vector2D>
			{
				r2->rect.Left().begin,
				r2->rect.Left().end,
				r2->rect.Right().begin,
				r2->rect.Right().end
			};

			r1Closest = r1vtc[0];

			for (size_t i = 1; i < r1vtc.size(); i++)
			{
				float sqrDist = (r1Closest - pointOfContact).SquareMagnitude();

				if ((r1vtc[i] - pointOfContact).SquareMagnitude() < sqrDist)
				{
					r1Closest = r1vtc[i];
				}

			}

			r2Closest = r2vtc[0];

			for (size_t i = 1; i < r2vtc.size(); i++)
			{
				float sqrDist = (r2Closest - pointOfContact).SquareMagnitude();

				if ((r2vtc[i] - pointOfContact).SquareMagnitude() < sqrDist)
				{
					r2Closest = r2vtc[i];
				}

			}

			focus = (r1Closest - pointOfContact).SquareMagnitude() < (r2Closest - pointOfContact).SquareMagnitude() ? &r2vtc : &r1vtc;
			std::vector<Vector2D> linePts = std::vector<Vector2D>();
			for (size_t i = 0; i < 2; i++)
			{
				Vector2D closest = (*focus)[0];
				int closestIndex = 0;
				for (size_t j = 1; j < focus->size(); j++)
				{
					float sqrDist = (closest - pointOfContact).SquareMagnitude();

					if (((*focus)[i] - pointOfContact).SquareMagnitude() < sqrDist)
					{
						closest = (*focus)[i];
						closestIndex = i;
					}
				}

				focus->erase(focus->begin() + closestIndex);
				linePts.push_back(closest);
			}

			normal = Vector2D::Normalize(linePts[0] - linePts[1]);
		}
		
		return normal;

	}
	else
	{
		throw std::runtime_error("Both objects must have colliders!");
	}
}

std::vector<PhysicsObject*> PhysicsHandler::GetPhysicsObjects()
{
	return objects;
}

void PhysicsHandler::Initialize()
{
	layerMatrix = Matrix<bool>(layerCount);

	for (size_t i = 0; i < layerCount; i++)
	{
		for (size_t j = 0; j < layerCount; j++)
		{
			layerMatrix[i][j] = true;
		}
	}

}